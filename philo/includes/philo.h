/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:37:12 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/01/11 11:54:33 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define INVALID_ARGS "Invalid arguments!"
# define MALLOC_ERROR "Malloc error!"
# define INIT_MUTEX "Failed to initalize mutex!"
# define CREATE_THREAD "Failed to create thread!"
# define JOIN_THREAD "Failed to join thread!"

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_args
{
	int		nb_philo;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	int		max_meals;
}				t_args;

typedef struct s_philo
{
	int				id;
	t_args			*args;
	int				meals_count;
	size_t			start_time;
	size_t			last_meal;
	pthread_mutex_t	fork;
	pthread_mutex_t	*data;
	pthread_mutex_t	*print;
	pthread_t		thread;
	struct s_philo	*next;
}				t_philo;

void	ft_puterr(char *s, t_args *args, t_philo **philos);
t_args	*parse_args(int ac, char **av);

#endif