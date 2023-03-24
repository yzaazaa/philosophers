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
		philos[i].fork_couple = get_forks(wrapper, i);
		philos[i].meals_count = 0;
		philos[i].time_left = wrapper->args->time_to_die + ft_time();
		if(pthread_mutex_init(&philos[i].philo_mutex, 0) != 0)
			ft_error(ERROR_MUTEX_INIT);
		i++;
	}
	return(philos);
}

void	ft_sleep(size_t time, t_wrapper *wrapper)
{
	time += ft_time();
	while(wrapper->args->running && time > ft_time())
		usleep(100);
}

void	ft_eat(t_params *params)
{
	pthread_mutex_lock(&params->philo->fork_couple[0]->fork_mutex);
	ft_log(TAKEN_FORK, params->wrapper, params->philo->philo_id);
	if(!params->philo->fork_couple[1])
	{
		ft_sleep(params->wrapper->args->time_to_die * 2, params->wrapper);
		return ;
	}
	pthread_mutex_lock(&params->philo->fork_couple[1]->fork_mutex);
	ft_log(TAKEN_FORK, params->wrapper, params->philo->philo_id);
	pthread_mutex_lock(&params->philo->philo_mutex);
	ft_log(EATING, params->wrapper, params->philo->philo_id);
	params->philo->time_left = ft_time() + params->wrapper->args->time_to_die;
	pthread_mutex_unlock(&params->philo->philo_mutex);
	ft_sleep(params->wrapper->args->time_to_eat, params->wrapper);
	pthread_mutex_lock(&params->philo->philo_mutex);
	params->philo->meals_count++;
	pthread_mutex_unlock(&params->philo->philo_mutex);
	pthread_mutex_unlock(&params->philo->fork_couple[1]->fork_mutex);
	pthread_mutex_unlock(&params->philo->fork_couple[0]->fork_mutex);
}

void	*loop(void *params)
{
	t_params	*philo_wrapper;

	philo_wrapper = (t_params *)params;
	if(philo_wrapper->philo->philo_id % 2)
		ft_sleep(philo_wrapper->wrapper->args->time_to_eat, philo_wrapper->wrapper);
	while(philo_wrapper->wrapper->args->running)
	{
		ft_eat(philo_wrapper);
		if(!philo_wrapper->wrapper->args->running)
			return (0);
		ft_log(SLEEPING, philo_wrapper->wrapper, philo_wrapper->philo->philo_id);
		ft_sleep(philo_wrapper->wrapper->args->time_to_sleep, philo_wrapper->wrapper);
		if(!philo_wrapper->wrapper->args->running)
			return (0);
		ft_log(THINKING, philo_wrapper->wrapper, philo_wrapper->philo->philo_id);
	}
	return (0);
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