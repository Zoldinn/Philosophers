/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:05:03 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/13 17:40:25 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	wait_start(t_waiter *waiter)
{
	pthread_mutex_lock(&waiter->mutex);
	while (!waiter->start)
	{
		pthread_mutex_unlock(&waiter->mutex);
		usleep(100);
		pthread_mutex_lock(&waiter->mutex);
	}
	pthread_mutex_unlock(&waiter->mutex);
}

void	go_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork[LEFT]->mutex);
		ft_log(philo->waiter, TAKE_A_FORK, philo->id, 0);
		pthread_mutex_lock(&philo->fork[RIGHT]->mutex);
		ft_log(philo->waiter, TAKE_A_FORK, philo->id, 0);
	}
	else
	{
		pthread_mutex_lock(&philo->fork[RIGHT]->mutex);
		ft_log(philo->waiter, TAKE_A_FORK, philo->id, 0);
		pthread_mutex_lock(&philo->fork[LEFT]->mutex);
		ft_log(philo->waiter, TAKE_A_FORK, philo->id, 0);
	}
	philo_lock(1, philo);
	philo->last_meal = philo->waiter->time;
	philo->meal_count++;
	ft_log(philo->waiter, EAT, philo->id, philo->waiter->tte);
	philo_lock(0, philo);

	pthread_mutex_unlock(&philo->fork[LEFT]->mutex);
	pthread_mutex_unlock(&philo->fork[RIGHT]->mutex);
}

// last meal 			: avant de manger
// commencer starvation : juste apres manger
//
// doivent tous commencer en meme temps
void	*routine(void *arg)
{
	t_waiter	*waiter;
	t_philo		*philo;

	philo = (t_philo *) arg;
	waiter = philo->waiter;

	wait_start(waiter);

	waiter_lock(1, waiter);
	while (!waiter->stop)
	{
		waiter_lock(0, waiter);
		philo_lock(1, philo);
		if (waiter->mml && philo->meal_count >= waiter->mml)
		{
			philo->eaten_enough = 1;
			return (waiter_lock(0, waiter), philo_lock(0, philo), NULL);
		}
		philo_lock(0, philo);
		go_eat(philo);
		ft_log(waiter, SLEEP, philo->id, waiter->tts);
		ft_log(waiter, THINK, philo->id, 0);
	}
	waiter_lock(0, waiter);
	return (NULL);
}
