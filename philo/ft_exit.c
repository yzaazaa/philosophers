/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:39 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/24 18:58:27 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

void	ft_exit(char *err_msg, t_data **data)
{
	(void)data;
	// if (*data && (*data)->args)
	// 	free((*data)->args);
	// if ((*data))
	// 	free_data(*data);
	if (err_msg)
		write(2, err_msg, ft_strlen(err_msg));
	exit(1);
}