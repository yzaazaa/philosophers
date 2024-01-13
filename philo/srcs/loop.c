/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 10:11:10 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/01/13 11:53:06 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	did_philo_die(t_philo *philo)
{
	t_philo	*tmp;
	int		i;
	int		philo_full;

	tmp = philo;
	i = 0;
	philo_full = 0;
	while (i++ < philo->args->nb_philo)
	{
		if (tmp->meals_count == tmp->args->max_meals)
			philo_full++;
		if (ft_time() - tmp->last_meal >= tmp->args->time_to_die)
		{
			pthread_mutex_lock(tmp->print);
			printf("%zu %d %s", ft_time() - tmp->start_time, tmp->id, DIED);
			return (1);
		}
		tmp = tmp->next;
	}
	if (philo_full == i)
	{
		printf("Simulation stopped!\n");
		return (1);
	}
	return (0);
}

static int	philo_eat(t_philo *philo)
{
	if (did_philo_die(philo))
		return (1);
	pthread_mutex_lock(&philo->fork);
	if (did_philo_die(philo))
		return (1);
	pthread_mutex_lock(philo->print);
	printf("%zu %d %s\n", ft_time() - philo->start_time, philo->id, TAKEN_FORK);
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(&philo->next->fork);
	if (did_philo_die(philo))
		return (1);
	pthread_mutex_lock(philo->print);
	printf("%zu %d %s\n", ft_time() - philo->start_time, philo->id, TAKEN_FORK);
	pthread_mutex_unlock(philo->print);
	if (did_philo_die(philo))
		return (1);
	pthread_mutex_lock(philo->print);
	printf("%zu %d %s\n", ft_time() - philo->start_time, philo->id, EATING);
	pthread_mutex_unlock(philo->print);
	ft_usleep(philo->args->time_to_eat, philo->start_time);
	pthread_mutex_lock(philo->data);
	philo->meals_count++;
	pthread_mutex_unlock(philo->data);
	return (0);
}

static int	philo_sleep(t_philo *philo)
{
	if (did_philo_die(philo))
		return (1);
	pthread_mutex_lock(philo->print);
	printf("%zu %d %s\n", ft_time() - philo->start_time, philo->id, SLEEPING);
	pthread_mutex_unlock(philo->print);
	ft_usleep(philo->args->time_to_sleep, philo->start_time);
	return (0);
}

static int	philo_think(t_philo *philo)
{
	if (did_philo_die(philo))
		return (1);
	pthread_mutex_lock(philo->print);
	printf("%zu %d %s\n", ft_time() - philo->start_time, philo->id, THINKING);
	pthread_mutex_unlock(philo->print);
	return (0);
}


int	ft_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	*loop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->args->nb_philo == 1)
	{
		ft_usleep(philo->args->time_to_die, philo->start_time);
		printf("%zu %d %s\n", ft_time() - philo->start_time, philo->id, DIED);
		return (NULL);
	}
	while (1 || (philo->args->max_meals > 0 && philo->meals_count != philo->args->max_meals))
	{
		if (philo_eat(philo))
			return (NULL);
		if (philo_sleep(philo))
			return (NULL);
		if (philo_think(philo))
			return (NULL);
	}
	return (NULL);
}