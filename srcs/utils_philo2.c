/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:27:13 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/20 18:07:57 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_log(int philo_id, t_waiter *waiter, char *str)
{
	if (!waiter->print.created)
		return ;
	pthread_mutex_lock(&waiter->print.mutex);
	if (get_shared(&waiter->stop) != 1
		|| ft_cmpstr(str, "\e[31mdied\e[0m") == 0)
		printf("%ld %s%d%s %s\n", now(waiter), YELLOW, philo_id, NC, str);
	pthread_mutex_unlock(&waiter->print.mutex);
}

long	now(t_waiter *waiter)
{
	return (get_time() - waiter->start_t.ldata);
}

void	increment_shared(t_shared *shared)
{
	if (!shared || !shared->created)
		return ;
	pthread_mutex_lock(&shared->mutex);
	shared->data += 1;
	pthread_mutex_unlock(&shared->mutex);
}
