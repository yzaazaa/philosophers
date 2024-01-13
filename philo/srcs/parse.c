/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:03:23 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/01/13 11:39:28 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_puterr(char *s, t_args *args, t_philo **philos)
{
	if (philos && *philos)
		destroy_philos(philos);
	if (args)
		free(args);
	if (s)
		printf("%s\n", s);
	exit(1);
}

int	ft_atoi(char *str, t_args *args)
{
	int		i;
	long	res;
	long	tmp;

	i = 0;
	res = 0;
	if (str[0] == '-')
		ft_puterr(INVALID_ARGS, args, NULL);
	if (str[0] == '+')
		i++;
	if (str[i] == '\0')
		ft_puterr(INVALID_ARGS, args, NULL);
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = (res * 10) + (str[i] - '0');
		if (tmp > INT_MAX)
			ft_puterr(INVALID_ARGS, args, NULL);
		res = tmp;
		i++;
	}
	if (str[i] != '\0')
		ft_puterr(INVALID_ARGS, args, NULL);
	return (res);
}

t_args	*parse_args(int ac, char **av)
{
	t_args	*args;

	if (ac != 5 && ac != 6)
		ft_puterr(INVALID_ARGS, NULL, NULL);
	args = malloc(sizeof(t_args));
	args->nb_philo = ft_atoi(av[1], args);
	if (args->nb_philo < 1)
		ft_puterr(INVALID_ARGS, args, NULL);
	args->time_to_die = ft_atoi(av[2], args);
	args->time_to_eat = ft_atoi(av[3], args);
	args->time_to_sleep = ft_atoi(av[4], args);
	if (ac == 6)
		args->max_meals = ft_atoi(av[5], args);
	else
		args->max_meals = -1;
	return (args);
}