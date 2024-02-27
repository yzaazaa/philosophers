/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:43:40 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/27 19:39:28 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_exit(MALLOC_ERR, NULL), 1);
	memset(data, 0, sizeof(t_data));
	if (check_args(ac, av, data))
		return (1);
	if (init_data(data))
		return (1);
	watch_death(data);
	ft_exit(NULL, &data);
	return (0);
}
