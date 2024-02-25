/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:21:41 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/25 00:25:52 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <limits.h>

# define INVALID_ARGS "Invalid arguments!\n"
# define MALLOC_ERR "Malloc error!\n"

# define FORK_TAKEN "has taken a fork\n"
# define IS_EATING "is eating\n"
# define IS_SLEEPING "is sleeping\n"
# define IS_THINKING "is thinking\n"
# define DIED "died\n"

typedef struct s_args
{
	int	nb_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	max_meals;
}				t_args;

typedef struct s_philo
{
	pthread_t		philo;
	pthread_mutex_t	mutex;
	int				time;
	int				id;
	int				meals_eaten;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	t_args			*args;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	data_mutex;
	int				time;
}				t_data;


void	ft_exit(char *err_msg, t_data **data);
void	check_args(int ac, char **av, t_data *data);
void	init_data(t_data *data);
void	init_args(t_args *args, t_data *data);
void	*routine(void *arg);
void	ft_print(t_philo *philo, char *s, int flag);
int		get_time(void);
void	manage_philos(t_data *data);

#endif