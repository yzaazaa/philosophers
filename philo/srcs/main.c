/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:40:39 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/01/11 11:26:36 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"


int	main(int ac, char **av)
{
	t_philo	*philos;
	t_args	*args;

	philos = NULL;
	args = malloc(sizeof(args));
	if (!args)
		ft_puterr(MALLOC_ERROR, NULL, NULL);
	args = parse_args(ac, av);
	create_philos(&philos, args);
}