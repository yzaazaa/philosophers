/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:40:48 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/27 01:07:34 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_print(t_philo *philo, char *s, int flag)
{
	sem_wait(philo->data->data_sem);
	if (s)
		printf("%ld %d %s", ft_time() - philo->data->time, philo->id, s);
	if (flag)
		sem_post(philo->data->data_sem);
}
