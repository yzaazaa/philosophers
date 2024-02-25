/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:46:54 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/25 01:42:44 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_threads(t_data *data)
{
	int	i;
	int	nb_philos;

	nb_philos = data->args->nb_philos;
	i = -1;
	data->time = get_time();
	while (++i < nb_philos)
	{
		data->philos[i].time = data->time;
		pthread_create(&data->philos[i].philo, NULL, routine, &data->philos[i]);
	}
	i = -1;
	while (++i < nb_philos)
		pthread_detach(data->philos[i].philo);
}

void	init_data(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->args->nb_philos);
	if (!data->philos)
		ft_exit(MALLOC_ERR, &data);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->args->nb_philos);
	if (!data->forks)
		ft_exit(MALLOC_ERR, &data);
	i = -1;
	while (++i < data->args->nb_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->philos[i].mutex, NULL);
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].meals_eaten = 0;
	}
	pthread_mutex_init(&data->data_mutex, NULL);
	init_threads(data);
}