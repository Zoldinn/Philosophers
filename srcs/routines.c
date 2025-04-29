/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:33:34 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/29 17:53:37 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philo_routine(void *arg)
{
	t_waiter	*w;

	w = (t_waiter *) arg;

	pthread_mutex_lock(&w->philo->fork[LEFT]->mutex);
	w->philo->fork[LEFT]->taken = 1;
	pthread_mutex_lock(&w->print_mutex);
	printf("philo %s%d%s take fork %s%d%s\n", RED, w->philo->id, NC, RED, w->philo->fork[LEFT]->id, NC);
	pthread_mutex_unlock(&w->print_mutex);

	pthread_mutex_lock(&w->philo->fork[RIGHT]->mutex);
	w->philo->fork[RIGHT]->taken = 1;
	pthread_mutex_lock(&w->print_mutex);
	printf("philo %s%d%s take fork %s%d%s\n", RED, w->philo->id, NC, RED, w->philo->fork[RIGHT]->id, NC);
	pthread_mutex_unlock(&w->print_mutex);

	pthread_mutex_lock(&w->print_mutex);
	if (w->philo->fork[LEFT]->taken == 1 && w->philo->fork[RIGHT]->taken == 1)
	{
		
		printf("philo %s%d%s is eating\n\n", RED, w->philo->id, NC);
	}
	pthread_mutex_unlock(&w->print_mutex);

	w->philo->fork[RIGHT]->taken = 0;
	pthread_mutex_unlock(&w->philo->fork[RIGHT]->mutex);
	w->philo->fork[LEFT]->taken = 0;
	pthread_mutex_unlock(&w->philo->fork[LEFT]->mutex);

	return (NULL);
}
