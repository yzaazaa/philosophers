/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:17:48 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/01/11 11:55:16 by yzaazaa          ###   ########.fr       */
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

static void create_threads(t_philo **philos)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	tmp = *philos;
	while (i < (*philos)->args->nb_philo)
	{
		if (pthread_create(&tmp->thread, NULL, loop, (void *)tmp))
			ft_puterr(CREATE_THREAD, (*philos)->args, philos);
		tmp = tmp->next;
		i++;
	}
}

static void	join_threads(t_philo **philos)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	tmp = *philos;
	while (i < (*philos)->args->nb_philo)
	{
		if (pthread_join(tmp->thread, NULL))
			ft_puterr(JOIN_THREAD, (*philos)->args, philos);
		tmp = tmp->next;
		i++;
	}
}

static void handle_die(t_philo **philos)
{
	t_philo	*tmp;

	tmp = (*philos);
	if (ft_time() - tmp->last_meal >= tmp->args->time_to_die)
	{
		pthread_mutex_lock(tmp->print);
		printf("%zu %d died", ft_time(), tmp->id);
	}
	while (tmp->)
}

void	create_philo(t_philo **philos, t_args *args)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	while (i < args->nb_philo)
		push_philo(philos, new_philo(i++, args, philos));
	(*philos)->print = malloc(sizeof(phtread_mutex_t));
	if (!(*philos)->print)
		return (free((*philos)->print), ft_puterr(MALLOC_ERROR, (*philos)->args, philos));
	if (pthread_mutex_init((*philos)->print, NULL))
		return (free((*philos)->print), ft_puterr(MALLOC_ERROR, (*philos)->args, philos));
	(*philos)->data = malloc(sizeof(phtread_mutex_t));
	if (!(*philos)->data)
		return (free((*philos)->print), free((*philos)->data), ft_puterr(MALLOC_ERROR, (*philos)->args, philos));
	if (pthread_mutex_init((*philos)->data, NULL))
		return (free((*philos)->print), free((*philos)->data), ft_puterr(MALLOC_ERROR, (*philos)->args, philos));
	tmp = *philos;
	tmp->data = (*philos)->data;
	tmp->print = (*philos)->print;
	tmp = tmp->next;
	while (tmp != (*philos))
	{
		tmp->data = (*philos)->data;
		tmp->print = (*philos)->print;
		tmp = tmp->next;
	}
	create_threads(philos);
	handle_die(philos);
	join_threads(philos);
}
