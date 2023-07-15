/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:40:06 by isidki            #+#    #+#             */
/*   Updated: 2023/07/15 21:51:20 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_unlock_printf(t_philo *phl, char *str)
{
	time_t	t;

	t = phl->args->start_time;
	pthread_mutex_lock(&phl->args->lock_print);
	printf("%ld %d %s\n", ft_gettime() - t, phl->id, str);
	pthread_mutex_unlock(&phl->args->lock_print);
}

void	lock_printf(t_philo *phl, char *str)
{
	time_t	t;

	t = phl->args->start_time;
	pthread_mutex_lock(&phl->args->lock_print);
	printf("%ld %d %s\n", ft_gettime() - t, phl->id, str);
}

void	ft_unlock_destroy_mutexes(t_philo *philos)
{
	int	i;

	i = philos->args->nbr_of_philo;
	while (i--)
	{
		pthread_mutex_destroy(&philos->mutex_last_meal);
		pthread_mutex_destroy(&philos->mutex_nbr_meals);
		pthread_mutex_destroy(&philos->fork);
		philos = philos->next;
	}
	pthread_mutex_destroy(&philos->args->lock_print);
	pthread_mutex_destroy(&philos->args->mutex_stop);
}
