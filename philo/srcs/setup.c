/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:17:48 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/01/13 11:34:56 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static t_philo	*new_philo(int id, t_args *args, t_philo **philos)
{
	t_philo	*philo;

	philo = malloc(sizeof(philo));
	if (!philo)
		ft_puterr(MALLOC_ERROR, args, philos);
	philo->args = args;
	philo->last_meal = 0;
	philo->id = id;
	if (pthread_mutex_init(&philo->fork, NULL))
		ft_puterr(INIT_MUTEX, args, philos);
	philo->next = *philos;
	return (philo);
}

static void	push_philo(t_philo **philos, t_philo *new_philo)
{
	t_philo	*tmp;

	if (!philos)
		ft_puterr(NULL, new_philo->args, philos);
	if (!*philos)
	{
		*philos = new_philo;
		new_philo->next = new_philo;
		return ;
	}
	tmp = *philos;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_philo;
}

static void	init_mutexes(t_philo **philos)
{
	t_philo	*tmp;
	int		i;

	(*philos)->print = malloc(sizeof(pthread_mutex_t));
	if (!(*philos)->print)
		return (free((*philos)->print), ft_puterr(MALLOC_ERROR, (*philos)->args, philos));
	if (pthread_mutex_init((*philos)->print, NULL))
		return (free((*philos)->print), ft_puterr(MALLOC_ERROR, (*philos)->args, philos));
	(*philos)->data = malloc(sizeof(pthread_mutex_t));
	if (!(*philos)->data)
		return (free((*philos)->print), free((*philos)->data), ft_puterr(MALLOC_ERROR, (*philos)->args, philos));
	if (pthread_mutex_init((*philos)->data, NULL))
		return (free((*philos)->print), free((*philos)->data), ft_puterr(MALLOC_ERROR, (*philos)->args, philos));
	tmp = *philos;
	i = 0;
	while (i++ < (*philos)->args->nb_philo)
	{
		tmp->data = (*philos)->data;
		tmp->print = (*philos)->print;
		tmp = tmp->next;
	}
}

void	create_philos(t_philo **philos, t_args *args)
{
	int		i;

	i = 0;
	while (i < args->nb_philo)
		push_philo(philos, new_philo(i++, args, philos));
	init_mutexes(philos);
}

void	ft_usleep(size_t time_to_sleep, size_t start_time)
{
	while (time_to_sleep <= start_time + ft_time())
		usleep(1);
}