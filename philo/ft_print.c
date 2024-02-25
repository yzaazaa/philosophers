/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:40:48 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/25 19:52:37 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *philo, char *s, int flag)
{
	pthread_mutex_lock(&philo->data->data_mutex);
	if (s)
		printf("%ld %d %s", ft_time() - philo->data->time, philo->id, s);
	if (flag)
		pthread_mutex_unlock(&philo->data->data_mutex);
}