/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:00:50 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/24 20:05:07 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int time)
{
	int	time_now;

	time_now = get_time();
	while (get_time() - time_now < time)
		usleep(50);
}

void	manage_forks(t_philo *philo, int lock)
{
	if (lock == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
		ft_print(philo, FORK_TAKEN, 1);
		if (philo->id == philo->data->args->nb_philos)
			pthread_mutex_lock(&philo->data->forks[0]);
		else
			pthread_mutex_lock(&philo->data->forks[philo->id]);
		ft_print(philo, FORK_TAKEN, 1);
	}
	else if (lock == 1)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
		if (philo->id == philo->data->args->nb_philos)
			pthread_mutex_unlock(&philo->data->forks[0]);
		else
			pthread_mutex_unlock(&philo->data->forks[philo->id]);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
	{
		printf("philo %d is sleeping\n", philo->id);
		ft_usleep(philo->data->args->time_to_eat / 2);
	}
	while (philo->meals_eaten < philo->data->args->max_meals)
	{
		manage_forks(philo, 0);
		ft_print(philo, IS_EATING, 1);
		philo->meals_eaten++;
		ft_usleep(philo->data->args->time_to_eat);
		manage_forks(philo, 1);
		philo->time = get_time();
		ft_print(philo, IS_SLEEPING, 1);
		ft_usleep(philo->data->args->time_to_sleep);
		ft_print(philo, IS_THINKING, 1);
	}
}