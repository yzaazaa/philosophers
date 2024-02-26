/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watch_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 03:37:21 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/26 08:09:05 by yzaazaa          ###   ########.fr       */
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

void	*watch_death(t_philo *philo)
{
	while (420)
	{
		if (philo->data->args->max_meals != -1 && philo->meals_eaten == philo->data->args->max_meals)
			philo->data->philos_full++;
		if (philo->data->philos_full == philo->data->args->nb_philos)
		{
			philo->dead = 1;
			ft_print(philo, NULL, 0);
			sem_post(philo->data->finished);
		}
		if (ft_time() - philo->time >= philo->data->args->time_to_die)
		{
			philo->dead = 1;
			ft_print(philo, DIED, 0);
			sem_post(philo->data->finished);
			// kill_processes(philo->data);
			// ft_exit(NULL, &philo->data);
		}
		usleep(100);
	}
	return (NULL);
}