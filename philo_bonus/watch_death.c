/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watch_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 03:37:21 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/27 21:20:35 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_processes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->args->nb_philos)
		kill(data->pid[i], SIGKILL);
}

void	*check_philos_full(void *arg)
{
	int		i;
	t_data	*data;

	i = -1;
	data = (t_data *)arg;
	while (++i < data->args->nb_philos)
	{
		sem_wait(data->full);
		usleep(100);
	}
	sem_post(data->finished);
	return (NULL);
}

void	*watch_death(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = -1;
	ft_sleep(philo->data->args->time_to_die / 2);
	while (!philo->dead)
	{
		if (ft_time() - philo->time >= philo->data->args->time_to_die)
		{
			philo->dead = 1;
			ft_print(philo, DIED, 0);
			while (++i < philo->data->args->nb_philos)
				sem_post(philo->data->full);
			sem_post(philo->data->finished);
		}
		usleep(100);
	}
	return (NULL);
}
