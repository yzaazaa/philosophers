/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 03:20:44 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/26 07:38:57 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	routine(t_philo *philo)
{
	while (!philo->dead && philo->meals_eaten < philo->data->args->max_meals)
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
	t_philo	philo;

	philo.data = data;
	philo.id = id + 1;
	philo.dead = 0;
	philo.meals_eaten = 0;
	philo.time = ft_time();
	if (pthread_create(&philo.deah_watcher, NULL, (void *)watch_death, &data))
		ft_exit(THREAD_ERR, &data);
	// // while (data->start != 1)
	// // 	usleep(10);
	// printf("zabi\n");
	routine(&philo);
	if (pthread_detach(philo.deah_watcher))
		ft_exit(THREAD_DETACH_ERR, &data);
}
