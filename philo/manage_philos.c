/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:13:34 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/25 01:48:09 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eat(int *philos_ate_max_meals, t_philo *philo, t_args args)
{
	pthread_mutex_lock(&philo->mutex);
	if (philo->meals_eaten >= args.max_meals)
		(*philos_ate_max_meals)++;
	pthread_mutex_unlock(&philo->mutex);
	if (*philos_ate_max_meals == args.nb_philos)
	{
		ft_print(philo, NULL, 0);
		return (0);
	}
	return (1);
}

void	init_args(t_args *args, t_data *data)
{
	pthread_mutex_lock(&data->data_mutex);
	args->max_meals = data->args->max_meals;
	args->nb_philos = data->args->nb_philos;
	args->time_to_die = data->args->time_to_die;
	args->time_to_eat = data->args->time_to_eat;
	args->time_to_sleep = data->args->time_to_sleep;
	pthread_mutex_unlock(&data->data_mutex);
}

static int	check_time(t_philo *philo, t_args args)
{
	if (get_time() - philo->time >= args.time_to_die)
		return (0);
	return (1);
}

void	manage_philos(t_data *data)
{
	int	i;
	int	philos_ate_max_meals;
	t_args	args;

	init_args(&args, data);
	i = 0;
	philos_ate_max_meals = 0;
	while (420)
	{
		if (i == args.nb_philos)
			i = 0;
		pthread_mutex_lock(&data->data_mutex);
		pthread_mutex_lock(&data->philos[i].mutex);
		if (args.max_meals != -1 && !eat(&philos_ate_max_meals, &data->philos[i], args))
			return ;
		pthread_mutex_unlock(&data->philos[i].mutex);
		pthread_mutex_unlock(&data->data_mutex);
		pthread_mutex_lock(&data->philos[i].mutex);
		if (!check_time(&data->philos[i], args))
		{
			ft_print(&data->philos[i], DIED, 0);
			return ;
		}
		pthread_mutex_unlock(&data->philos[i].mutex);
		i++;
	}
}
