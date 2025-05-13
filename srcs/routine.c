/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:05:03 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/13 11:42:35 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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

void	go_eat(t_philo *philo, int i)
{
	if (i % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork[LEFT]->mutex);
		ft_log(philo->waiter, TAKE_A_FORK, philo->id, 0);
		pthread_mutex_lock(&philo->fork[RIGHT]->mutex);
		ft_log(philo->waiter, TAKE_A_FORK, philo->id, 0);
		pthread_mutex_lock(&philo->last_meal_mutex);
		philo->last_meal = get_time();
		philo->meal_count++;
		ft_log(philo->waiter, EAT, philo->id, philo->waiter->tte);
		pthread_mutex_unlock(&philo->last_meal_mutex);
		pthread_mutex_unlock(&philo->fork[LEFT]->mutex);
		pthread_mutex_unlock(&philo->fork[RIGHT]->mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->fork[LEFT]->mutex);
		ft_log(philo->waiter, TAKE_A_FORK, philo->id, 0);
		pthread_mutex_lock(&philo->fork[RIGHT]->mutex);
		ft_log(philo->waiter, TAKE_A_FORK, philo->id, 0);
		pthread_mutex_lock(&philo->last_meal_mutex);
		philo->last_meal = get_time();
		philo->meal_count++;
		ft_log(philo->waiter, EAT, philo->id, philo->waiter->tte);
		pthread_mutex_unlock(&philo->last_meal_mutex);
		pthread_mutex_unlock(&philo->fork[LEFT]->mutex);
		pthread_mutex_unlock(&philo->fork[RIGHT]->mutex);
	}
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
	while (!waiter->stop && i < waiter->nbp)
	{
		philo = &((*philos)[++i]);
		go_eat(philo, i);
		ft_log(waiter, THINK, philo->id, waiter->ttt);
		ft_log(waiter, SLEEP, philo->id, waiter->tts);
	}
	return (NULL);
}