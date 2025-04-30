/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:33:34 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/30 12:12:44 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;

	pthread_mutex_lock(&philo->fork[LEFT]->mutex);
	philo->fork[LEFT]->taken = 1;
	pthread_mutex_lock(&philo->waiter->print_mutex);
	printf("philo %s%d%s take fork %s%d%s\n", RED, philo->id, NC, RED, philo->fork[LEFT]->id, NC);
	pthread_mutex_unlock(&philo->waiter->print_mutex);

	pthread_mutex_lock(&philo->fork[RIGHT]->mutex);
	philo->fork[RIGHT]->taken = 1;
	pthread_mutex_lock(&philo->waiter->print_mutex);
	printf("philo %s%d%s take fork %s%d%s\n", RED, philo->id, NC, RED, philo->fork[RIGHT]->id, NC);
	pthread_mutex_unlock(&philo->waiter->print_mutex);

	pthread_mutex_lock(&philo->waiter->print_mutex);
	if (philo->fork[LEFT]->taken == 1 && philo->fork[RIGHT]->taken == 1)
	{
		philo->last_meal = get_time();
		philo->meal_count += 1;
		printf("philo %s%d%s is eating\n\n", RED, philo->id, NC);
	}
	pthread_mutex_unlock(&philo->waiter->print_mutex);

	philo->fork[RIGHT]->taken = 0;
	pthread_mutex_unlock(&philo->fork[RIGHT]->mutex);
	philo->fork[LEFT]->taken = 0;
	pthread_mutex_unlock(&philo->fork[LEFT]->mutex);

	return (NULL);
}
