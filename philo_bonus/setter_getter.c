/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter_getter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:40:47 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/26 20:04:17 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	get_value(sem_t	*semaphore, int *value)
{
	int	ret;

	sem_wait(semaphore);
	ret = *value;
	sem_post(semaphore);
	return (ret);
}

void	set_value(sem_t *semaphore, int *to_set, int value)
{
	sem_wait(semaphore);
	*to_set = value;
	sem_post(semaphore);
}

long	get_time(sem_t *semaphore, long *time)
{
	long	ret;

	sem_wait(semaphore);
	ret = *time;
	sem_post(semaphore);
	return (ret);
}

void	set_time(sem_t *semaphore, long *to_set, long time)
{
	sem_wait(semaphore);
	*to_set = time;
	sem_post(semaphore);
}