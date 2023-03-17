#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_args
{
	size_t	philo_count;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	max_meals;
	int		running;
}	t_args;

typedef struct s_fork
{
	size_t			fork_id;
	pthread_mutex_t	lock;
}	t_fork;


typedef struct s_philo
{
	size_t			philo_id;
	pthread_t		thread;
	size_t			meals_number;
	size_t			time_left;
	t_args			*args;
	t_fork			*fork;
	pthread_mutex_t	lock;
}	t_philo;

t_args	*ft_parser(int ac, char **av);

#endif