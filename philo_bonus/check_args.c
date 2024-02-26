/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:19:49 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/26 03:36:00 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_atoi(char *str, t_data **data)
{
	int		i;
	long	res;
	long	tmp;

	i = 0;
	res = 0;
	if (str[0] == '-')
		ft_exit(INVALID_ARGS, data);
	if (str[0] == '+')
		i++;
	if (!str[i])
		ft_exit(INVALID_ARGS, data);
	while (ft_isdigit(str[i]))
	{
		tmp = res * 10 + str[i] - '0';
		if (res > INT_MAX)
			ft_exit(INVALID_ARGS, data);
		res = tmp;
		i++;
	}
	if (str[i])
		ft_exit(INVALID_ARGS, data);
	return (res);
}

void	check_args(int ac, char **av, t_data *data)
{
	t_args	*args;

	if (ac != 5 && ac != 6)
		ft_exit(INVALID_ARGS, NULL);
	args = malloc(sizeof(t_args));
	if (!args)
		ft_exit(MALLOC_ERR, NULL);
	data->args = args;
	args->nb_philos = ft_atoi(av[1], &data);
	args->time_to_die = ft_atoi(av[2], &data);
	args->time_to_eat = ft_atoi(av[3], &data);
	args->time_to_sleep = ft_atoi(av[4], &data);
	if (args->nb_philos < 1 || args->nb_philos > 200
		|| args->time_to_die < 60 || args->time_to_eat < 60
		|| args->time_to_sleep < 60)
		ft_exit(INVALID_ARGS, &data);
	if (ac == 6)
		args->max_meals = ft_atoi(av[5], &data);
	else
		args->max_meals = -1;
}