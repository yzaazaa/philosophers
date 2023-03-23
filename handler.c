#include "philo.h"

t_params	*generate_params(t_wrapper *wrapper)
{
	t_params	*params;
	size_t		i;

	params = (t_params *)malloc(sizeof(t_params) * wrapper->args->number_of_philosophers);
	if(!params)
		ft_error(ERROR_MALLOC);
	params->wrapper = wrapper;
	i = 0;
	while(i < wrapper->args->number_of_philosophers)
	{
		params[i].philo = &wrapper->philos[i];
		i++;
	}
	return (params);
}

void	ft_handler(t_wrapper *wrapper)
{
	size_t	i;
	int		max_meals;

	while(wrapper->args->running)
	{
		i = 0;
		max_meals = wrapper->args->max_number_of_meals;
		while(wrapper->args->running && i < wrapper->args->number_of_philosophers)
		{
			pthread_mutex_lock(&wrapper->philos[i].philo_mutex);
			if(wrapper->philos[i].time_left < ft_time())
			{
				ft_log(DIED, wrapper, i);
				wrapper->args->running = 0;
			}
			if(max_meals && wrapper->philos[i].meals_count < wrapper->args->max_number_of_meals)
				max_meals = 0;
			pthread_mutex_unlock(&wrapper->philos[i].philo_mutex);
			i++;
		}
		if(max_meals)
			wrapper->args->running = 0;
	}
}

int	thread(t_wrapper *wrapper)
{
	t_params	*params;
	size_t		i;

	wrapper->forks = generate_forks(wrapper->args);
	wrapper->fork_couples = generate_fork_couples(wrapper);
	wrapper->philos = generate_philos(wrapper);
	params = generate_params(wrapper);
	if(!wrapper->args || !wrapper->forks || !params)
		return (0);
	i = 0;
	while(i < wrapper->args->number_of_philosophers)
	{
		if(pthread_create(&wrapper->philos[i].thread, 0, &loop, (void *) &params[i]) != 0)
			ft_error(ERROR_CREATE_THREAD);
		i++;
	}
	ft_handler(wrapper);
	i = 0;
	while(i < wrapper->args->number_of_philosophers)
	{
		if(pthread_join(wrapper->philos[i].thread, 0) != 0)
			ft_error(ERROR_JOIN_THREAD);
		i++;
	}
	return (1);
}