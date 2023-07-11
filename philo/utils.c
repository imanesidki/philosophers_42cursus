/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:02:33 by isidki            #+#    #+#             */
/*   Updated: 2023/07/11 16:51:32 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			break ;
	}
	if (!str[i])
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	long	n;

	n = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (!*str || *str == '-' || *str == '+')
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		n = n * 10 + *str++ - '0';
		if (n > 2147483647)
			return (-1);
	}
	return (n);
}

time_t	ft_gettime(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_usleep(time_t t)
{
	time_t	tm;

	tm = ft_gettime();
	while (ft_gettime() < tm + t)
		usleep(100);
}
