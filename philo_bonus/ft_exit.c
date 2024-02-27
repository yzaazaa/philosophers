/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:39 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/27 01:24:50 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_strlen(const char *s)
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
	if ((*data)->forks && (*data)->forks != SEM_FAILED)
		sem_close((*data)->forks);
	if ((*data)->data_sem && (*data)->data_sem != SEM_FAILED)
		sem_close((*data)->data_sem);
	if ((*data)->finished && (*data)->finished != SEM_FAILED)
		sem_close((*data)->finished);
	if ((*data)->start && (*data)->start != SEM_FAILED)
		sem_close((*data)->start);
	sem_unlink("forks");
	sem_unlink("data_sem");
	sem_unlink("finished");
	sem_unlink("full");
	sem_unlink("start");
	if ((*data)->pid)
		free((*data)->pid);
	if ((*data)->philos)
		free((*data)->philos);
	free(*data);
}

void	ft_exit(char *err_msg, t_data **data)
{
	if (data && *data)
		free_data(data);
	if (err_msg)
		write(2, err_msg, ft_strlen(err_msg));
	exit(0);
}
