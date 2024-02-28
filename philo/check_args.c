/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:19:49 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/27 22:07:59 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_atoi(char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	if (str[0] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res);
}

static int	check_arg(char *str)
{
	int		i;
	long	res;
	long	tmp;

	i = 0;
	res = 0;
	if (str[0] == '-')
		return (1);
	if (str[0] == '+')
		i++;
	if (!str[i])
		return (1);
	while (ft_isdigit(str[i]))
	{
		tmp = res * 10 + str[i] - '0';
		if (res > INT_MAX)
			return (1);
		res = tmp;
		i++;
	}
	if (str[i])
		return (1);
	return (0);
}

static int	check(t_data *data, t_args *args)
{
	if (args->nb_philos > 200)
		return (ft_exit(INVALID_ARGS, &data, -1, -1), 1);
	if (args->nb_philos < 1)
		return (ft_exit(NULL, &data, -1, -1), 1);
	if (args->max_meals == 0)
		return (ft_exit(NULL, &data, -1, -1), 1);
	return (0);
}

int	check_args(int ac, char **av, t_data *data)
{
	t_args	*args;

	if (ac != 5 && ac != 6)
		return (ft_exit(INVALID_ARGS, &data, -1, -1), 1);
	args = malloc(sizeof(t_args));
	if (!args)
		return (ft_exit(MALLOC_ERR, &data, -1, -1), 1);
	data->args = args;
	if (ac == 6)
		args->max_meals = ft_atoi(av[5]);
	else
		args->max_meals = -1;
	while (--ac > 1)
		if (check_arg(av[ac]))
			return (ft_exit(INVALID_ARGS, &data, -1, -1), 1);
	args->nb_philos = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	if (check(data, args))
		return (1);
	return (0);
}
