/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter_getter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:40:47 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/27 02:26:35 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_value(pthread_mutex_t *mutex, int *value)
{
	int	ret;

	pthread_mutex_lock(mutex);
	ret = *value;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	set_value(pthread_mutex_t *mutex, int *to_set, int value)
{
	pthread_mutex_lock(mutex);
	*to_set = value;
	pthread_mutex_unlock(mutex);
}

long	get_time(pthread_mutex_t *mutex, long *time)
{
	long	ret;

	pthread_mutex_lock(mutex);
	ret = *time;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	set_time(pthread_mutex_t *mutex, long *to_set, long time)
{
	pthread_mutex_lock(mutex);
	*to_set = time;
	pthread_mutex_unlock(mutex);
}
