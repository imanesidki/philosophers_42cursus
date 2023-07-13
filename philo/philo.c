/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:02:28 by isidki            #+#    #+#             */
/*   Updated: 2023/07/13 17:47:17 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_args	*args;
	t_philo	*philos;

	args = malloc(sizeof(t_args));
	if (ft_parsing(ac, av) == -1 || fill_in_args(ac, av, args) == -1)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	philos = create_philos(args);
	if (create_threads(philos, args) == -1)
	{
		ft_lstclear(&philos, args);
		return (1);
	}
	check_time_to_die(philos);
	//seg problem
	ft_unlock_destroy_mutexes(philos);
	ft_lstclear(&philos, args);
	return (0);
}
