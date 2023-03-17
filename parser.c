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
			return (0);
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
		printf("Number of arguments invalid !\n");
		exit(0);
	}
	args = (t_args *)malloc(sizeof(t_args));
	if(!args)
	{
		printf("Error allocating memory !\n");
		exit(0);
	}
	args->philo_count = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	if(ac == 6)
		args->max_meals = ft_atoi(av[5]);
	if(!args->philo_count || !args->time_to_die || !args->time_to_eat || !args->time_to_eat || 
		(ac == 6 && !args->max_meals))
	{
		printf("Arguments invalid !\n");
		exit(0);
	}
	return (args);
}