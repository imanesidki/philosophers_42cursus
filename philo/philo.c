/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:57:09 by isidki            #+#    #+#             */
/*   Updated: 2023/07/10 21:35:37 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_parsing(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 5 && ac != 6)
		return (-1);
	while (++i < ac)
	{
		if (!ft_isdigit(av[i]) || ft_atoi(av[i]) == 0 || ft_atoi(av[i]) == -1)
			return (-1);
	}
	return (0);
}

int	fill_in_args(int ac, char **av, t_args *args)
{
	args->nbr_of_philo = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->min_must_eat = -1;
	args->start_time = ft_gettime();
	if (ac == 6)
		args->min_must_eat = ft_atoi(av[5]);
	if (args->nbr_of_philo >= 200 || args->time_to_die <= 60
		|| args->time_to_eat <= 60 || args->time_to_sleep <= 60)
		return (-1);
	pthread_mutex_init(&args->lock_print, NULL);
	return (0);
}

void	lock_unlock_printf(t_philo *phl, char *str)
{
	time_t	t;

	t = phl->args.start_time;
	pthread_mutex_lock(&phl->args.lock_print);
	printf("%ld_in_ms %d %s\n", ft_gettime() - t, phl->id, str);
	pthread_mutex_unlock(&phl->args.lock_print);
}

void	lock_printf(t_philo *phl, char *str)
{
	time_t	t;

	t = phl->args.start_time;
	pthread_mutex_lock(&phl->args.lock_print);
	printf("%ld_in_ms %d %s\n", ft_gettime() - t, phl->id, str);
}

void	mini_start_routine(t_philo *phl)
{
	pthread_mutex_lock(&phl->fork);
	lock_unlock_printf(phl, "has taken a fork");
	pthread_mutex_lock(&(phl->next->fork));
	lock_unlock_printf(phl, "has taken a fork");
	pthread_mutex_lock(&phl->mutex_last_meal);
	phl->last_meal = ft_gettime();
	pthread_mutex_unlock(&phl->mutex_last_meal);
	pthread_mutex_lock(&phl->mutex_nbr_meals);
	phl->nbr_meals++;
	pthread_mutex_unlock(&phl->mutex_nbr_meals);
	lock_unlock_printf(phl, "is eating");
	ft_usleep(phl->args.time_to_eat);
	pthread_mutex_unlock(&phl->fork);
	pthread_mutex_unlock(&phl->next->fork);
}

void	*start_routine(void *philo)
{
	t_philo	*phl;

	phl = (t_philo *)philo;
	pthread_mutex_lock(&phl->mutex_last_meal);
	phl->last_meal = ft_gettime();
	pthread_mutex_unlock(&phl->mutex_last_meal);
	if (phl->id % 2 == 0)
		usleep(100);
	while (1)
	{
		mini_start_routine(phl);
		lock_unlock_printf(phl, "is sleeping");
		ft_usleep(phl->args.time_to_sleep);
		lock_unlock_printf(phl, "is thinking");
	}
}

t_philo	*create_philos(t_args *args)
{
	int		i;
	t_philo	*philos;

	i = 1;
	philos = NULL;
	while (i <= args->nbr_of_philo)
	{
		ft_lstadd_back(&philos, ft_lstnew(args, i));
		i++;
	}
	return (philos);
}

int	create_threads(t_philo *philos, t_args *args)
{
	int	i;

	i = 1;
	while (i <= args->nbr_of_philo)
	{
		if (pthread_create(&philos->pid, NULL, &start_routine, philos) != 0)
			return (-1);
		if (pthread_detach(philos->pid) != 0)
			return (-1);
		philos = philos->next;
		i++;
	}
	return (0);
}

int	check_death(t_philo *philos)
{
	time_t	t;
	time_t	tm;

	tm = philos->args.time_to_die;
	pthread_mutex_lock(&philos->mutex_last_meal);
	t = philos->last_meal;
	if ((ft_gettime() - t) > tm)
	{
		lock_printf(philos, "died");
		return (1);
	}
	pthread_mutex_unlock(&philos->mutex_last_meal);
	return (0);
}

void	check_time_to_die(t_philo *philos)
{
	int		min_must_eat;
	int		count;

	min_must_eat = philos->args.min_must_eat;
	count = 0;
	while (1)
	{
		usleep(100);
		if (check_death(philos))
			return ;
		pthread_mutex_lock(&philos->mutex_nbr_meals);
		if (philos->nbr_meals == philos->args.min_must_eat)
			count++;
		if (count == philos->args.nbr_of_philo)
		{
			pthread_mutex_lock(&philos->args.lock_print);
			return ;
		}
		pthread_mutex_unlock(&philos->mutex_nbr_meals);
		philos = philos->next;
	}
}

void	ft_unlock_destroy_mutexes(t_philo *philos)
{
	int	i;

	i = philos->args.nbr_of_philo;
	while (i--)
	{
		pthread_mutex_destroy(&philos->mutex_last_meal);
		pthread_mutex_destroy(&philos->mutex_nbr_meals);
		pthread_mutex_destroy(&philos->fork);
		philos = philos->next;
	}
	pthread_mutex_destroy(&philos->args.lock_print);
}

int	main(int ac, char **av)
{
	t_args	args;
	t_philo	*philos;

	if (ft_parsing(ac, av) == -1 || fill_in_args(ac, av, &args) == -1)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	philos = create_philos(&args);
	if (create_threads(philos, &args) == -1)
		return (1);
	check_time_to_die(philos);
	ft_unlock_destroy_mutexes(philos);
	ft_lstclear(&philos);
	return (0);
}
