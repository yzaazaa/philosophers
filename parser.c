#include "philo.h"

size_t	ft_atoi(const char *nptr)
{
	size_t	ret;
	char 	*ptr;

	ret = 0;
	ptr = (char *)nptr;
	if(!ptr)
		return (0);
	while(*ptr >= 0 && *ptr <= 32)
		ptr++;
	if(*ptr == '-' || *ptr == '+')
	{
		if(*ptr == '-')
		{
			printf("Arguments can not be negative !\n");
			exit(0);
		}
		ptr++;
	}
	while(*ptr >= '0' && *ptr <= '9')
	{
		ret = ret * 10 + (*ptr - '0');
		ptr++;
	}
	return (ret);
}

t_args	*ft_parser(int ac, char **av)
{
	t_args	*args;

	if(ac != 5 && ac != 6)
	{
		printf("Arguments invalid !\n");
		exit(0);
	}
	args = (t_args *)malloc(sizeof(t_args));
	if(!args)
	{
		printf("Error allocating memory !\n");
		exit(0);
	}
	args->number_of_philosophers = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	if(ac == 6)
		args->max_number_of_meals = ft_atoi(av[5]);
	args->running = 1;
	return (args);
}