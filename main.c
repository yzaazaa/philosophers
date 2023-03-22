#include "philo.h"

t_wrapper	*wrapper_init(int ac, char **av)
{
	t_wrapper	*wrapper;

	wrapper = (t_wrapper *)malloc(sizeof(t_wrapper));
	if(!wrapper)
		ft_error(ERROR_MALLOC);
	pthread_mutex_init(&wrapper->wrapper_mutex, 0);
	wrapper->args = ft_parser(ac, av);
	wrapper->forks = generate_forks(wrapper->args);
	wrapper->fork_couples = generate_fork_couples(wrapper);
	wrapper->philos = generate_philos(wrapper);
	return (wrapper);
}

int	main(int ac, char **av)
{
	t_wrapper	*wrapper;
/* 	size_t		i; */

	wrapper = wrapper_init(ac, av);
	/* TESTS*/
	/* printf("%zu %zu %zu %zu %zu %d\n", wrapper->args->number_of_philosophers, wrapper->args->time_to_die, wrapper->args->time_to_eat, wrapper->args->time_to_sleep, wrapper->args->max_number_of_meals, wrapper->args->running);
	i = 0;
	while(i < wrapper->args->number_of_philosophers)
	{
		printf("Fork number %zu\n", wrapper->forks[i].fork_id);
		i++;
	}
	i = 0;
	while(i < wrapper->args->number_of_philosophers)
	{
		printf("Couple %zu : [%zu,%zu]\n", i, wrapper->fork_couples[i][0].fork_id, wrapper->fork_couples[i][1].fork_id);
		i++;
	}
	i = 0;
	while(i < wrapper->args->number_of_philosophers)
	{
		printf("I am philosopher number %zu, my left fork is fork number %zu and my right fork is fork number %zu\n", wrapper->philos[i].philo_id, wrapper->philos[i].fork_couple[1].fork_id, wrapper->philos[i].fork_couple[0].fork_id);
		i++;
	} */
	destroy_philos(wrapper);
	destroy_fork_couples(wrapper);
	destroy_forks(wrapper);
	free(wrapper->args);
	free(wrapper);
}