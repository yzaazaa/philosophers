/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:39 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/25 20:27:37 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

static void	free_data(t_data **data)
{
	int	i;
	int	nb_philos;

	if ((*data)->args)
	{
		nb_philos = (*data)->args->nb_philos;
		free((*data)->args);
	}
	if ((*data)->philos)
	{
		i = -1;
		while (++i < nb_philos)
		{
			pthread_mutex_destroy(&(*data)->philos[i].time_mutex);
			pthread_mutex_destroy(&(*data)->philos[i].meals_mutex);
		}
		free((*data)->philos);
	}
	if ((*data)->forks)
	{
		i = -1;
		while (++i < nb_philos)
			pthread_mutex_destroy(&(*data)->forks[i]);
		free((*data)->forks);
	}
	pthread_mutex_destroy(&(*data)->data_mutex);
}

void	ft_exit(char *err_msg, t_data **data)
{
	if (data && *data)
		free_data(data);
	if (err_msg)
		write(2, err_msg, ft_strlen(err_msg));
	exit(1);
}