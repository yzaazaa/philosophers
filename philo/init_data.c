/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:46:54 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/27 21:07:11 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_threads(t_data *data)
{
	int	i;
	int	nb_philos;

	nb_philos = data->args->nb_philos;
	i = -1;
	while (++i < nb_philos)
		if (pthread_create(&data->philos[i].philo, NULL,
				routine, &data->philos[i]))
			return (ft_exit(THREAD_ERR, &data, -1, 4), 1);
	set_time(&data->data_mutex, &data->time, ft_time());
	set_value(&data->data_mutex, &data->start, 1);
	i = -1;
	while (++i < nb_philos)
		if (pthread_detach(data->philos[i].philo))
			return (ft_exit(THREAD_DETACH_ERR, &data, -1, 4), 1);
	return (0);
}

static void	init_philo(t_data *data, t_philo *philo, int i)
{
	philo->id = i + 1;
	philo->data = data;
	philo->is_full = 0;
	philo->meals_eaten = 0;
	philo->l_fork = &data->forks[philo->id - 1];
	if (philo->id == data->args->nb_philos)
		philo->r_fork = &data->forks[0];
	else
		philo->r_fork = &data->forks[philo->id];
}

int	init_data(t_data *data)
{
	int	i;

	data->start = 0;
	data->philos = malloc(sizeof(t_philo) * data->args->nb_philos);
	if (!data->philos)
		return (ft_exit(MALLOC_ERR, &data, -1, -1), 1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->args->nb_philos);
	if (!data->forks)
		return (ft_exit(MALLOC_ERR, &data, -1, -1), 1);
	i = -1;
	while (++i < data->args->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (ft_exit(MUTEX_ERR, &data, i, 0), 1);
		if (pthread_mutex_init(&data->philos[i].meals_mutex, NULL))
			return (ft_exit(MUTEX_ERR, &data, i, 1), 1);
		if (pthread_mutex_init(&data->philos[i].time_mutex, NULL))
			return (ft_exit(MUTEX_ERR, &data, i, 2), 1);
		init_philo(data, &data->philos[i], i);
	}
	if (pthread_mutex_init(&data->data_mutex, NULL))
		return (ft_exit(MUTEX_ERR, &data, 1, 3), 1);
	if (init_threads(data))
		return (1);
	return (0);
}
