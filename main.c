#include "philo.h"

int	main(int ac, char **av)
{
	t_wrapper	*wrapper;
	size_t		i;

	wrapper = (t_wrapper *)malloc(sizeof(t_wrapper));
	if(!wrapper)
	{
		printf("Error allocating memory !\n");
		exit(0);
	}
	wrapper->args = ft_parser(ac, av);
	wrapper->forks = generate_forks(wrapper->args);
	i = 0;
	while(i < wrapper->args->number_of_philosophers)
	{
		printf("Fork number %zu\n", wrapper->forks[i].fork_id);
		i++;
	}
	wrapper->fork_couples = generate_fork_couples(wrapper);
	i = 0;
	while(i < wrapper->args->number_of_philosophers)
	{
		printf("Couple %zu : [%zu,%zu]\n", i, wrapper->fork_couples[i][0].fork_id, wrapper->fork_couples[i][1].fork_id);
		i++;
	}
	destroy_fork_couples(wrapper);
	destroy_forks(wrapper);
	free(wrapper->args);
	free(wrapper);
}