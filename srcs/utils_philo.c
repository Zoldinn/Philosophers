/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:07:40 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/21 12:12:16 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// return the time is ms (milisec)
// to have actual time (time start - actual time)
long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

// Lock, int shared->data = value, and unlock
void	set_shared(t_shared *shared, int value)
{
	if (!shared || !shared->created)
		return ;
	pthread_mutex_lock(&shared->mutex);
	shared->data = value;
	pthread_mutex_unlock(&shared->mutex);
}

// Same as set_shared but set the long ldata value
void	set_lshared(t_shared *shared, long value)
{
	if (!shared || !shared->created)
		return ;
	pthread_mutex_lock(&shared->mutex);
	shared->ldata = value;
	pthread_mutex_unlock(&shared->mutex);
}

// Lock, retourne la valeur int data de shared et unlock
int	get_shared(t_shared *shared)
{
	int	value;

	if (!shared || !shared->created)
		return (0);
	pthread_mutex_lock(&shared->mutex);
	value = shared->data;
	pthread_mutex_unlock(&shared->mutex);
	return (value);
}

// Same as get_shared but for the long ldata
long	get_lshared(t_shared *shared)
{
	long	value;

	if (!shared || !shared->created)
		return (0);
	pthread_mutex_lock(&shared->mutex);
	value = shared->ldata;
	pthread_mutex_unlock(&shared->mutex);
	return (value);
}
