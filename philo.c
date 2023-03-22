#include "philo.h"

t_philo	*generate_philos(t_wrapper *wrapper)
{
	t_philo	*philos;
	size_t	i;

	philos = (t_philo *)malloc(sizeof(t_philo) * wrapper->args->number_of_philosophers);
	if(!philos)
		ft_error(ERROR_MALLOC);
	i = 0;
	while(i < wrapper->args->number_of_philosophers)
	{
		philos[i].philo_id = i;
		philos[i].fork_couple = wrapper->fork_couples[i];
		if(pthread_mutex_init(&philos[i].philo_mutex, 0) != 0)
			ft_error(ERROR_MUTEX_INIT);
		i++;
	}
	return(philos);
}

void	destroy_philos(t_wrapper *wrapper)
{
	size_t	i;

	i = 0;
	while(i < wrapper->args->number_of_philosophers)
	{
		pthread_mutex_destroy(&wrapper->philos[i].philo_mutex);
		i++;
	}
	free(wrapper->philos);
}