/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:39 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/26 03:47:55 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

static void	free_data(t_data **data)
{
	if ((*data)->args)
		free((*data)->args);
	sem_close((*data)->forks);
	sem_close((*data)->data_sem);
	sem_unlink("forks");
	sem_unlink("data_sem");
	if ((*data)->pid)
		free((*data)->pid);
	free(*data);
}

void	ft_exit(char *err_msg, t_data **data)
{
	if (data && *data)
		free_data(data);
	if (err_msg)
		write(2, err_msg, ft_strlen(err_msg));
	exit(1);
}
