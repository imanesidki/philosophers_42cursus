/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:57:09 by isidki            #+#    #+#             */
/*   Updated: 2023/07/11 16:38:14 by isidki           ###   ########.fr       */
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
	args->count = 0;
	args->start_time = ft_gettime();
	if (ac == 6)
		args->min_must_eat = ft_atoi(av[5]);
	if (args->nbr_of_philo >= 200 || args->time_to_die <= 60
		|| args->time_to_eat <= 60 || args->time_to_sleep <= 60)
		return (-1);
	pthread_mutex_init(&args->lock_print, NULL);
	return (0);
}
