/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:00:50 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/25 01:45:37 by yzaazaa          ###   ########.fr       */
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

void	manage_forks(t_philo *philo, int lock, t_args args)
{
	if (lock == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
		ft_print(philo, FORK_TAKEN, 1);
		pthread_mutex_lock(&philo->mutex);
		if (philo->id == args.nb_philos)
			pthread_mutex_lock(&philo->data->forks[0]);
		else
			pthread_mutex_lock(&philo->data->forks[philo->id]);
		pthread_mutex_unlock(&philo->mutex);
		ft_print(philo, FORK_TAKEN, 1);
	}
	else if (lock == 1)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
		pthread_mutex_lock(&philo->mutex);
		if (philo->id == args.nb_philos)
			pthread_mutex_unlock(&philo->data->forks[0]);
		else
			pthread_mutex_unlock(&philo->data->forks[philo->id]);
		pthread_mutex_unlock(&philo->mutex);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_args	args;
	int		nb_meals;

	philo = (t_philo *)arg;
	init_args(&args, philo->data);
	if (!(philo->id % 2))
		ft_usleep(args.time_to_eat / 2);
	while (420)
	{
		pthread_mutex_lock(&philo->mutex);
		nb_meals = philo->meals_eaten;
		pthread_mutex_unlock(&philo->mutex);
		if (args.max_meals == -1 || (args.max_meals != -1 && nb_meals < args.max_meals))
		{
			manage_forks(philo, 0, args);
			ft_print(philo, IS_EATING, 1);
			philo->time = get_time();
			philo->meals_eaten++;
			ft_usleep(args.time_to_eat);
			manage_forks(philo, 1, args);
			ft_print(philo, IS_SLEEPING, 1);
			ft_usleep(args.time_to_sleep);
			ft_print(philo, IS_THINKING, 1);
		}
	}
	return (NULL);
}