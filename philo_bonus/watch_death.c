/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watch_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 03:37:21 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/26 07:41:49 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_processes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->args->nb_philos)
		kill(data->pid[i], SIGSEGV);
}

void	*watch_death(t_philo *philo)
{
	while (420)
	{
		if (philo->data->args->max_meals != -1 && philo->meals_eaten == philo->data->args->max_meals)
			return (NULL);
		if (ft_time() - philo->time >= philo->data->args->time_to_die)
		{
			philo->dead = 1;
			ft_print(philo, DIED, 0);
			kill_processes(philo->data);
			ft_exit(NULL, &philo->data);
		}
		usleep(100);
	}
	return (NULL);
}