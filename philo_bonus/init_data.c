/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 03:08:22 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/26 07:37:31 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_data(t_data *data)
{
	int	i;

	data->start = 0;
	sem_unlink("forks");
	sem_unlink("data_sem");
	data->forks = sem_open("forks", O_CREAT, 0700, data->args->nb_philos);
	data->data_sem = sem_open("data_sem", O_CREAT, 0700, 1);
	if (data->forks == SEM_FAILED || data->data_sem == SEM_FAILED)
		ft_exit(SEM_FAIL, &data);
	data->pid = malloc(sizeof(int) * data->args->nb_philos);
	if (!data->pid)
		ft_exit(MALLOC_ERR, &data);
	i = -1;
	data->start = 1;
	data->time = ft_time();
	while (++i < data->args->nb_philos)
	{
		data->pid[i] = fork();
		if (data->pid[i] == 0)
			process(data, i);
		else if (data->pid[i] == -1)
			ft_exit(FORK_ERR, &data);
	}
	sem_wait(data->data_sem);
	sem_post(data->data_sem);
	i = -1;
	while (++i < data->args->nb_philos)
		waitpid(data->pid[i++], 0, 0);
}
