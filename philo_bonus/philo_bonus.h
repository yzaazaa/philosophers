/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 22:31:24 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/26 08:05:35 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <pthread.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>

# define INVALID_ARGS "Invalid arguments!\n"
# define MALLOC_ERR "Failed to allocate memory!\n"
# define MUTEX_ERR "Failed to initialize mutex!\n"
# define SEM_FAIL "Failed to open semaphore!\n"
# define THREAD_ERR "Failed to create thread!\n"
# define THREAD_DETACH_ERR "Failed to detach thread!\n"
# define FORK_ERR "Resource temporarily unavailable\n"

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
	long	max_meals;
}				t_args;

typedef struct s_philo
{
	pthread_t		deah_watcher;
	long			time;
	int				id;
	int				meals_eaten;
	int				is_full;
	int				dead;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	t_args			*args;
	t_philo			*philos;
	sem_t			*data_sem;
	sem_t			*finished;
	sem_t			*forks;
	int				*pid;
	long			time;
	int				start;
	int				philos_full;
}				t_data;

void	check_args(int ac, char **av, t_data *data);
void	init_data(t_data *data);
long	ft_time(void);
void	ft_sleep(long time);
void	ft_print(t_philo *philo, char *s, int flag);
void	process(t_data *data, int id);
void	*watch_death(t_philo *philo);
void	kill_processes(t_data *data);
void	ft_exit(char *err_msg, t_data **data);

#endif