/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:07:40 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/13 17:50:26 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// return the time is ms (milisec)
// to have actual time (time start - actual time)
long	get_time()
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

int	ft_log(t_waiter *waiter, t_state state, int philo_id, int waiting)
{
	pthread_mutex_lock(&waiter->mutex);
	printf("%ld %ld", (get_time() - waiter->start_time), philo_id);
	if (state == TAKE_A_FORK)
		printf(" has taken a fork\n", 18);
	else if (state == EAT)
		printf(" is eating\n");
	else if (state == THINK)
		printf(" is thinking\n");
	else if (state == SLEEP)
		printf(" is sleeping\n");
	else if (state == DIE)
		printf(" died\n");
	usleep(waiting * 1000);
	pthread_mutex_unlock(&waiter->mutex);
	return (0);
}
