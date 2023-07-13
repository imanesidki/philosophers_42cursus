/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:40:06 by isidki            #+#    #+#             */
/*   Updated: 2023/07/13 17:34:25 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philos)
{
	time_t	t;
	time_t	tm;

	tm = philos->args->time_to_die;
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
	while (1)
	{
		usleep(100);
		if (check_death(philos))
			return ;
		pthread_mutex_lock(&philos->mutex_nbr_meals);
		if (philos->args->count == philos->args->nbr_of_philo)
		{
			pthread_mutex_lock(&philos->args->lock_print);
			return ;
		}
		pthread_mutex_unlock(&philos->mutex_nbr_meals);
		philos = philos->next;
	}
}
