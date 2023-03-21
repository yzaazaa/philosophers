#include "philo.h"

t_fork	*generate_forks(t_args	*args)
{
	t_fork	*forks;
	size_t	i;

	forks = (t_fork *)malloc(args->number_of_philosophers * sizeof(t_fork));
	if(!forks)
	{
		printf("Error allocating memory !\n");
		exit(0);
	}
	i = 0;
	while(i < args->number_of_philosophers)
	{
		forks[i].fork_id = i;
		pthread_mutex_init(&forks[i].fork_mutex, 0);
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

t_fork	**generate_fork_couples(t_wrapper *wrapper)
{
	t_fork	**fork_couples;
	size_t	i;

	fork_couples = (t_fork **)malloc(sizeof(t_fork *) * wrapper->args->number_of_philosophers);
	if(!fork_couples)
	{
		printf("Error allocating memory !\n");
		exit(0);
	}
	i = 0;
	while(i < wrapper->args->number_of_philosophers)
	{
		fork_couples[i] = (t_fork *)malloc(sizeof(t_fork) * 2);
		if(!fork_couples[i])
		{
			printf("Error allocating memory !\n");
			exit(0);
		}
		fork_couples[i][0] = wrapper->forks[i];
		if(i > 0)
			fork_couples[i][1] = wrapper->forks[i - 1];
		else if(i == 0 && wrapper->args->number_of_philosophers > 1)
			fork_couples[i][1] = wrapper->forks[wrapper->args->number_of_philosophers - 1];
		i++;
	}
	return (fork_couples);
}

void	destroy_fork_couples(t_wrapper *wrapper)
{
	size_t	i;

	i = 0;
	while(i < wrapper->args->number_of_philosophers)
	{
		free(wrapper->fork_couples[i]);
		i++;
	}
	free(wrapper->fork_couples);
}