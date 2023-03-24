#include "philo.h"

t_fork	*generate_forks(t_args	*args)
{
	t_fork	*forks;
	size_t	i;

	forks = (t_fork *)malloc(args->number_of_philosophers * sizeof(t_fork));
	if(!forks)
		ft_error(ERROR_MALLOC);
	i = 0;
	while(i < args->number_of_philosophers)
	{
		forks[i].fork_id = i;
		if(pthread_mutex_init(&forks[i].fork_mutex, 0) != 0)
			ft_error(ERROR_MUTEX_INIT);
		i++;
	}
	return (forks);
}


void	destroy_forks(t_wrapper *wrapper)
{
	size_t	i;

	i = 0;
	while(i < wrapper->args->number_of_philosophers)
	{
		pthread_mutex_destroy(&wrapper->forks[i].fork_mutex);
		i++;
	}
	free(wrapper->forks);
}

t_fork	**get_forks(t_wrapper *wrapper, size_t id)
{
	t_fork	**fork_couple;

	fork_couple = (t_fork **)malloc(sizeof(t_fork *) * 2);
	if(!fork_couple)
		ft_error(ERROR_MALLOC);
	fork_couple[0] = &wrapper->forks[id];
	if(id > 0)
		fork_couple[1] = &wrapper->forks[id - 1];
	else if(wrapper->args->number_of_philosophers > 1)
		fork_couple[1] = &wrapper->forks[wrapper->args->number_of_philosophers - 1];
	return (fork_couple);
}