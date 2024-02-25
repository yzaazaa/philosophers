/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:13:34 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/25 19:53:09 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eat(int *philos_ate_max_meals, t_philo *philo)
{
	if (!philo->is_full && get_value(&philo->meals_mutex, &philo->meals_eaten) >= philo->data->args->max_meals)
	{
		philo->is_full = 1;
		(*philos_ate_max_meals)++;
	}
	if (*philos_ate_max_meals == philo->data->args->nb_philos)
	{
		ft_print(philo, NULL, 0);
		return (0);
	}
	return (1);
}

static int	check_time(t_philo *philo)
{
	if (ft_time() - get_time(&philo->time_mutex, &philo->time) >= philo->data->args->time_to_die)
		return (0);
	return (1);
}

void	manage_philos(t_data *data)
{
	int		i;
	int		philos_ate_max_meals;

	i = 0;
	philos_ate_max_meals = 0;
	ft_usleep(data->args->time_to_die / 2);
	while (420)
	{
		if (i == data->args->nb_philos)
			i = 0;
		if (data->args->max_meals != -1 && !eat(&philos_ate_max_meals, &data->philos[i]))
			return ;
		if (!check_time(&data->philos[i]))
		{
			ft_print(&data->philos[i], DIED, 0);
			return ;
		}
		i++;
	}
}
