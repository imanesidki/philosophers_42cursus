/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:57:09 by isidki            #+#    #+#             */
/*   Updated: 2023/07/15 22:38:38 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eating(t_philo *phl, int i)
{
	pthread_mutex_lock(&phl->mutex_last_meal);
	phl->last_meal = ft_gettime();
	pthread_mutex_unlock(&phl->mutex_last_meal);
	pthread_mutex_lock(&phl->mutex_nbr_meals);
	phl->nbr_meals++;
	if (phl->nbr_meals == i && i != -1)
		phl->args->count++;
	pthread_mutex_unlock(&phl->mutex_nbr_meals);
	lock_unlock_printf(phl, "is eating");
	ft_usleep(phl->args->time_to_eat);
}

void	mini_start_routine(t_philo *phl, int i)
{
	pthread_mutex_lock(&phl->args->mutex_stop);
	if (!phl->args->stop)
	{
		pthread_mutex_unlock(&phl->args->mutex_stop);
		return ;
	}
	pthread_mutex_unlock(&phl->args->mutex_stop);
	pthread_mutex_lock(&(phl->next->fork));
	lock_unlock_printf(phl, "has taken a fork");
	ft_eating(phl, i);
	pthread_mutex_unlock(&phl->fork);
	pthread_mutex_lock(&phl->args->mutex_stop);
	if (!phl->args->stop)
	{
		pthread_mutex_unlock(&phl->args->mutex_stop);
		return ;
	}
	pthread_mutex_unlock(&phl->args->mutex_stop);
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
		pthread_mutex_lock(&phl->fork);
		lock_unlock_printf(phl, "has taken a fork");
		mini_start_routine(phl, phl->args->min_must_eat);
		lock_unlock_printf(phl, "is sleeping");
		ft_usleep(phl->args->time_to_sleep);
		lock_unlock_printf(phl, "is thinking");
	}
	return (NULL);
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
