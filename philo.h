#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

/* ERRORS MACROS */

#define ERROR_MALLOC "Error allocating memory !"
#define ERROR_MUTEX_INIT "Error initializing mutex !"
#define ERROR_CREATE_THREAD "Error creating thread !"
#define ERROR_JOIN_THREAD "Error joining thread !"
#define ARGS_INVALID "Arguments invalid !"
#define ARGS_NEG "Arguments can not be negative !"

/* STATES MACROS */

#define TAKEN_FORK "has taken a fork"
#define EATING "is eating"
#define SLEEPING "is sleeping"
#define THINKING "is thinking"
#define DIED "died"

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
	t_fork			**fork_couple;
	size_t			time_left;
	size_t			meals_count;
	pthread_mutex_t	philo_mutex;
}	t_philo;

typedef	struct s_wrapper
{
	t_args			*args;
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	wrapper_mutex;
}	t_wrapper;

typedef	struct s_params
{
	t_philo		*philo;
	t_wrapper	*wrapper;
}	t_params;


void	ft_error(char *s);

t_args	*ft_parser(int ac, char **av);

t_fork	*generate_forks(t_args	*args);
t_fork	**get_forks(t_wrapper *wrapper, size_t id);
void	destroy_forks(t_wrapper *wrapper);

t_philo	*generate_philos(t_wrapper *wrapper);
void	destroy_philos(t_wrapper *wrapper);

size_t	ft_time();
void	ft_log(char *s, t_wrapper *wrapper, size_t id);

void	*loop(void *params);

int	thread(t_wrapper *wrapper);

#endif