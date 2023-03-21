#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_args
{
	size_t	number_of_philosophers;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	max_number_of_meals;
	int		running;
}	t_args;

typedef	struct s_fork
{
	size_t			fork_id;
	pthread_mutex_t	fork_mutex;
}	t_fork;

typedef	struct s_philo
{
	size_t			philo_id;
	pthread_t		thread;
	t_fork			*forks;
	pthread_mutex_t	philo_mutex;
}	t_philo;

typedef	struct s_wrapper
{
	t_args			*args;
	t_philo			*philos;
	t_fork			*forks;
	t_fork			**fork_couples;
	pthread_mutex_t	wrapper_mutex;
}	t_wrapper;


t_args	*ft_parser(int ac, char **av);

t_fork	*generate_forks(t_args	*args);
t_fork	**generate_fork_couples(t_wrapper *wrapper);
void	destroy_forks(t_wrapper *wrapper);
void	destroy_fork_couples(t_wrapper *wrapper);

#endif