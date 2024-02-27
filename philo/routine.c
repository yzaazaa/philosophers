/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:00:50 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/27 20:31:47 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	ft_print(philo, FORK_TAKEN, 1);
	pthread_mutex_lock(philo->r_fork);
	ft_print(philo, FORK_TAKEN, 1);
	set_value(&philo->meals_mutex, &philo->meals_eaten,
		get_value(&philo->meals_mutex, &philo->meals_eaten) + 1);
	set_time(&philo->time_mutex, &philo->time, ft_time());
	ft_print(philo, IS_EATING, 1);
	ft_sleep(philo->data->args->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!get_value(&philo->data->data_mutex, &philo->data->start))
		usleep(10);
	set_time(&philo->time_mutex, &philo->time,
		get_time(&philo->data->data_mutex, &philo->data->time));
	if (!(philo->id % 2))
		ft_sleep(philo->data->args->time_to_eat / 2);
	while (420)
	{
		eat(philo);
		ft_print(philo, IS_SLEEPING, 1);
		ft_sleep(philo->data->args->time_to_sleep);
		ft_print(philo, IS_THINKING, 1);
	}
	return (NULL);
}
