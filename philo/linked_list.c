/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:02:45 by isidki            #+#    #+#             */
/*   Updated: 2023/07/13 17:59:32 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*parcour;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		(*lst)->next = *lst;
		return ;
	}
	parcour = *lst;
	while (parcour->next != *lst)
		parcour = parcour->next;
	parcour->next = new;
	new->next = *lst;
}

t_philo	*ft_lstnew(t_args *args, int id)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof (t_philo));
	if (!philo)
		return (NULL);
	philo->args = args;
	philo->nbr_meals = 0;
	philo->id = id;
	pthread_mutex_init(&philo->fork, NULL);
	pthread_mutex_init(&philo->mutex_last_meal, NULL);
	pthread_mutex_init(&philo->mutex_nbr_meals, NULL);
	philo->next = NULL;
	return (philo);
}

void	ft_lstclear(t_philo **lst, t_args *args)
{
	t_philo	*parcour;
	t_philo	*l;

	if (!lst)
		return ;
	free(args);
	parcour = *lst;
	while (parcour->next != *lst)
	{
		l = parcour;
		parcour = parcour->next;
		free (l);
		l = NULL;
	}
	*lst = NULL;
}
