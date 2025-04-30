/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:33:34 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/30 16:33:41 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;

	pthread_mutex_lock(&philo->fork[LEFT]->mutex);

	pthread_mutex_lock(&philo->waiter->print_mutex);
	printf("philo %s%d%s take fork %s%d%s\n", RED, philo->id, NC, RED, philo->fork[LEFT]->id, NC);
	pthread_mutex_unlock(&philo->waiter->print_mutex);

	pthread_mutex_lock(&philo->fork[RIGHT]->mutex);

	pthread_mutex_lock(&philo->waiter->print_mutex);
	printf("philo %s%d%s take fork %s%d%s\n", RED, philo->id, NC, RED, philo->fork[RIGHT]->id, NC);
	pthread_mutex_unlock(&philo->waiter->print_mutex);

	pthread_mutex_lock(&philo->waiter->print_mutex);
	philo->last_meal = get_time();
	philo->meal_count += 1;
	printf("philo %s%d%s is %seating%s\n", RED, philo->id, NC, BLUE, NC);
	pthread_mutex_unlock(&philo->waiter->print_mutex);

	pthread_mutex_unlock(&philo->fork[RIGHT]->mutex);
	pthread_mutex_unlock(&philo->fork[LEFT]->mutex);

	return (NULL);
}

void	*waiter_routine(void *arg)
{
	t_waiter	*waiter;
	t_philo		*philo;
	int			i;

	waiter = (t_waiter *) arg;
	while (1)
	{
		i = -1;
		while (++i < waiter->nbp)
		{
			philo = &waiter->philo[0][i];
			if ((philo->last_meal - get_time()) > waiter->ttd
				|| philo->meal_count >= waiter->mml)
			{
				waiter->stop += 1;
				break ;
			}
		}
		usleep(10);
	}
	return (NULL);
}
