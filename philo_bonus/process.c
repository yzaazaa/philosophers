/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 03:20:44 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/26 08:13:31 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	routine(t_philo *philo)
{
	while (!philo->dead)
	{
		sem_wait(philo->data->forks);
		ft_print(philo, FORK_TAKEN, 1);
		sem_wait(philo->data->forks);
		ft_print(philo, FORK_TAKEN, 1);
		ft_print(philo, IS_EATING, 1);
		philo->time = ft_time();
		philo->meals_eaten++;
		ft_sleep(philo->data->args->time_to_eat);
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		ft_print(philo, IS_SLEEPING, 1);
		ft_sleep(philo->data->args->time_to_sleep);
		ft_print(philo, IS_THINKING, 1);
	}
}

void	process(t_data *data, int id)
{
	if (pthread_create(&data->philos[id].deah_watcher, NULL, (void *)watch_death, &data))
		ft_exit(THREAD_ERR, &data);
	if (pthread_detach(data->philos[id].deah_watcher))
		ft_exit(THREAD_DETACH_ERR, &data);
	data->philos[id].time = ft_time();
	routine(&data->philos[id]);
}
