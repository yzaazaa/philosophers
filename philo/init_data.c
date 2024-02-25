/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:46:54 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/25 20:33:04 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_threads(t_data *data)
{
	int	i;
	int	nb_philos;

	nb_philos = data->args->nb_philos;
	i = -1;
	while (++i < nb_philos)
		if (pthread_create(&data->philos[i].philo, NULL, routine, &data->philos[i]))
			ft_exit(THREAD_ERR, &data);
	set_time(&data->data_mutex, &data->time, ft_time());
	set_value(&data->data_mutex, &data->start, 1);
	i = -1;
	while (++i < nb_philos)
		if (pthread_detach(data->philos[i].philo))
			ft_exit(THREAD_DETACH_ERR, &data);
}

void	init_data(t_data *data)
{
	int	i;

	data->start = 0;
	data->philos = malloc(sizeof(t_philo) * data->args->nb_philos);
	if (!data->philos)
		ft_exit(MALLOC_ERR, &data);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->args->nb_philos);
	if (!data->forks)
		ft_exit(MALLOC_ERR, &data);
	i = -1;
	while (++i < data->args->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			ft_exit(MUTEX_ERR, &data);
		if (pthread_mutex_init(&data->philos[i].meals_mutex, NULL))
			ft_exit(MUTEX_ERR, &data);
		if (pthread_mutex_init(&data->philos[i].time_mutex, NULL))
			ft_exit(MUTEX_ERR, &data);
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].is_full = 0;
		data->philos[i].meals_eaten = 0;
		data->philos[i].l_fork = &data->forks[data->philos[i].id - 1];
		if (data->philos[i].id == data->args->nb_philos)
			data->philos[i].r_fork = &data->forks[0];
		else
			data->philos[i].r_fork = &data->forks[data->philos[i].id];
	}
	pthread_mutex_init(&data->data_mutex, NULL);
	init_threads(data);
}
