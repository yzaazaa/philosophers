/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 03:08:22 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/27 01:27:29 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_data(t_data *data)
{
	int		i;

	sem_unlink("forks");
	sem_unlink("data_sem");
	sem_unlink("finished");
	sem_unlink("full");
	sem_unlink("start");
	data->forks = sem_open("forks", O_CREAT, 0700, data->args->nb_philos);
	data->data_sem = sem_open("data_sem", O_CREAT, 0700, 1);
	data->finished = sem_open("finished", O_CREAT, 0700, 1);
	data->full = sem_open("full", O_CREAT, 0700, 1);
	data->start = sem_open("start", O_CREAT, 0700, data->args->nb_philos);
	if (data->forks == SEM_FAILED || data->data_sem == SEM_FAILED || data->finished == SEM_FAILED || data->full == SEM_FAILED || data->start == SEM_FAILED)
		ft_exit(SEM_FAIL, &data);
	sem_wait(data->finished);
	data->pid = malloc(sizeof(int) * data->args->nb_philos);
	if (!data->pid)
		ft_exit(MALLOC_ERR, &data);
	data->philos = malloc(sizeof(t_philo) * data->args->nb_philos);
	if (!data->philos)
		ft_exit(MALLOC_ERR, &data);
	i = -1;
	data->time = ft_time();
	if (pthread_create(&data->watch_meals, NULL, &check_philos_full, (void *)data))
		ft_exit(THREAD_ERR, &data);
	if (pthread_detach(data->watch_meals))
		ft_exit(THREAD_DETACH_ERR, &data);
	while (++i < data->args->nb_philos)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].dead = 0;
		data->philos[i].meals_eaten = 0;
		data->pid[i] = fork();
		if (data->pid[i] == 0)
			process(&data->philos[i]);
		else if (data->pid[i] == -1)
			ft_exit(FORK_ERR, &data);
	}
	i = -1;
	while (++i < data->args->nb_philos)
		sem_post(data->start);
	sem_wait(data->finished);
	kill_processes(data);
	ft_exit(NULL, &data);
}
