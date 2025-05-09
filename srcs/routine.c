/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:05:03 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/09 19:24:43 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include

void	wait_start(t_waiter *waiter)
{
	pthread_mutex_lock(&waiter->start_mutex);
	while (!waiter->start)
	{
		pthread_mutex_unlock(&waiter->start_mutex);
		usleep(100);
		pthread_mutex_lock(&waiter->start_mutex);
	}
	pthread_mutex_unlock(&waiter->start_mutex);
}

// last meal 			: avant de manger
// commencer starvation : juste apres manger
// 
// doivent tous commencer en meme temps
void	*routine(void *arg)
{
	t_waiter	*waiter;
	t_philo		**philos;
	t_philo		*philo;
	int			i;

	waiter = (t_waiter *) arg;
	philos = waiter->philo;
	wait_start(waiter);
	i = -1;
	while (!waiter->stop)
	{
		philo = &((*philos)[++i]);
		philo->last_meal_mutex
		log(waiter, EAT, philo->id, waiter->tte);
	}
	return (NULL);
}