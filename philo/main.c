/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:43:40 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/26 08:07:08 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		ft_exit(MALLOC_ERR, NULL);
	data->args = NULL;
	data->philos = NULL;
	data->forks = NULL;
	check_args(ac, av, data);
	init_data(data);
	manage_philos(data);
	ft_exit(NULL, &data);
}