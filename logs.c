#include "philo.h"

size_t	ft_time()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return	(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_log(char *s, t_wrapper *wrapper, size_t id)
{
	pthread_mutex_lock(&wrapper->wrapper_mutex);
	if(wrapper->args->running)
		printf("%zu %zu %s\n", ft_time(), id, s);
	pthread_mutex_unlock(&wrapper->wrapper_mutex);
}