/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:21:41 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/27 21:05:20 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>

# define INVALID_ARGS "Invalid arguments!\n"
# define MALLOC_ERR "Failed to allocate memory!\n"
# define MUTEX_ERR "Failed to initialize mutex!\n"
# define THREAD_ERR "Failed to create thread!\n"
# define THREAD_DETACH_ERR "Failed to detach thread!\n"

# define FORK_TAKEN "has taken a fork\n"
# define IS_EATING "is eating\n"
# define IS_SLEEPING "is sleeping\n"
# define IS_THINKING "is thinking\n"
# define DIED "died\n"

typedef struct s_args
{
	int		nb_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		max_meals;
}				t_args;

typedef struct s_philo
{
	pthread_t		philo;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	long			time;
	pthread_mutex_t	time_mutex;
	int				id;
	pthread_mutex_t	meals_mutex;
	int				meals_eaten;
	int				is_full;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	t_args			*args;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	data_mutex;
	long			time;
	int				start;
}				t_data;

int		get_value(pthread_mutex_t *mutex, int *value);
void	set_value(pthread_mutex_t *mutex, int *to_set, int value);
long	get_time(pthread_mutex_t *mutex, long *time);
void	set_time(pthread_mutex_t *mutex, long *to_set, long time);
void	ft_exit(char *err_msg, t_data **data, int j, int k);
int		check_args(int ac, char **av, t_data *data);
int		init_data(t_data *data);
void	*routine(void *arg);
void	ft_print(t_philo *philo, char *s, int flag);
long	ft_time(void);
void	watch_death(t_data *data);
void	ft_sleep(long time);

#endif