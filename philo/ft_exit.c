/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:39 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/27 22:00:18 by yzaazaa          ###   ########.fr       */
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

static void	destroy(t_data **data, int nb_philos, int j, int k)
{
	int	i;

	if ((*data)->philos)
	{
		i = -1;
		if (j != -1 && k != -1)
		{
			if (k != 1)
				while (++i < nb_philos)
					pthread_mutex_destroy(&(*data)->philos[i].meals_mutex);
			else
				while (++i < j)
					pthread_mutex_destroy(&(*data)->philos[i].meals_mutex);
			i = -1;
			if (k != 2)
				while (++i < nb_philos)
					pthread_mutex_destroy(&(*data)->philos[i].time_mutex);
			else
				while (++i < j)
					pthread_mutex_destroy(&(*data)->philos[i].time_mutex);
		}
		free((*data)->philos);
	}
}

static void	clean(t_data **data, int nb_philos, int j, int k)
{
	int	i;

	if ((*data)->forks)
	{
		i = -1;
		if (j != -1 && k != -1)
		{
			if (k != 0)
				while (++i < nb_philos)
					pthread_mutex_destroy(&(*data)->forks[i]);
			else
				while (++i < j)
					pthread_mutex_destroy(&(*data)->forks[i]);
		}
		free((*data)->forks);
	}
	destroy(data, nb_philos, j, k);
}

static void	free_data(t_data **data, int j, int k)
{
	int	nb_philos;

	nb_philos = 0;
	if ((*data)->args)
	{
		nb_philos = (*data)->args->nb_philos;
		free((*data)->args);
	}
	if (nb_philos)
		clean(data, nb_philos, j, k);
	if (k != 3)
		pthread_mutex_destroy(&(*data)->data_mutex);
	free((*data));
}

void	ft_exit(char *err_msg, t_data **data, int j, int k)
{
	if (data && *data)
		free_data(data, j, k);
	if (err_msg)
		write(2, err_msg, ft_strlen(err_msg));
}
