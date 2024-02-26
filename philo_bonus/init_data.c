/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 03:08:22 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/26 08:10:49 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_data(t_data *data)
{
	int	i;

	data->start = 0;
	data->philos_full = 0;
	sem_unlink("forks");
	sem_unlink("data_sem");
	sem_unlink("finished");
	data->forks = sem_open("forks", O_CREAT, 0700, data->args->nb_philos);
	data->data_sem = sem_open("data_sem", O_CREAT, 0700, 1);
	data->finished = sem_open("finished", O_CREAT, 0700, 1);
	sem_wait(data->finished);
	if (data->forks == SEM_FAILED || data->data_sem == SEM_FAILED || data->finished == SEM_FAILED)
		ft_exit(SEM_FAIL, &data);
	data->pid = malloc(sizeof(int) * data->args->nb_philos);
	if (!data->pid)
		ft_exit(MALLOC_ERR, &data);
	data->philos = malloc(sizeof(t_philo) * data->args->nb_philos);
	if (!data->philos)
		ft_exit(MALLOC_ERR, &data);
	i = -1;
	data->start = 1;
	data->time = ft_time();
	while (++i < data->args->nb_philos)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].dead = 0;
		data->philos[i].meals_eaten = 0;
		data->pid[i] = fork();
		if (data->pid[i] == 0)
			process(data, i);
		else if (data->pid[i] == -1)
			ft_exit(FORK_ERR, &data);
	}
	sem_wait(data->finished);
}
