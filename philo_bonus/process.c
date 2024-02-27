/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 03:20:44 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/27 21:20:20 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	routine(t_philo *philo)
{
	while (420)
	{
		sem_wait(philo->data->forks);
		ft_print(philo, FORK_TAKEN, 1);
		sem_wait(philo->data->forks);
		ft_print(philo, FORK_TAKEN, 1);
		ft_print(philo, IS_EATING, 1);
		set_time(philo->data->data_sem, &philo->time, ft_time());
		set_value(philo->data->data_sem, &philo->meals_eaten,
			get_value(philo->data->data_sem, &philo->meals_eaten) + 1);
		if (!philo->is_full && philo->data->args->max_meals != -1
			&& get_value(philo->data->data_sem, &philo->meals_eaten)
			== philo->data->args->max_meals)
		{
			philo->is_full = 1;
			sem_post(philo->data->full);
		}
		ft_sleep(philo->data->args->time_to_eat);
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		ft_print(philo, IS_SLEEPING, 1);
		ft_sleep(philo->data->args->time_to_sleep);
		ft_print(philo, IS_THINKING, 1);
	}
}

void	process(t_philo *philo)
{
	if (pthread_create(&philo->deah_watcher, NULL, watch_death, philo))
		ft_exit(THREAD_ERR, &philo->data);
	if (pthread_detach(philo->deah_watcher))
		ft_exit(THREAD_DETACH_ERR, &philo->data);
	sem_wait(philo->data->start);
	philo->time = ft_time();
	if (!(philo->id % 2))
		ft_sleep(philo->data->args->time_to_eat / 2);
	routine(philo);
}
