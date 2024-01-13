/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:40:39 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/01/13 11:35:36 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

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
		tmp->start_time = ft_time();
		tmp = tmp->next;
		i++;
	}
}

static void	handle_die(t_philo *philo)
{
	t_philo	*tmp;
	int		i;
	int		philo_full;

	while (1)
	{
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
				return ;
			}
			tmp = tmp->next;
		}
		if (philo_full == i)
		{
			printf("Simulation stopped!\n");
			return ;
		}
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

void	destroy_philos(t_philo **philos)
{
	t_philo	*tmp;
	t_philo	*tmp2;
	int		i;

	i = 0;
	tmp = (*philos);
	while (i < tmp->args->nb_philo - 1)
	{
		pthread_mutex_destroy(&tmp->fork);
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);		
	}
	pthread_mutex_destroy(tmp->data);
	free(tmp->data);
	pthread_mutex_destroy(tmp->print);
	free(tmp->print);
	free(tmp->args);
}

int	main(int ac, char **av)
{
	t_philo	*philos;
	t_args	*args;

	philos = NULL;
	args = malloc(sizeof(args));
	if (!args)
		ft_puterr(MALLOC_ERROR, NULL, NULL);
	args = parse_args(ac, av);
	create_philos(&philos, args);
	create_threads(&philos);
	handle_die(philos);
	join_threads(&philos);
	destroy_philos(&philos);
	return (0);
}