/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:05:03 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/20 12:03:02 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	go_eat(t_philo *phil)
{
	if (phil->id % 2 == 0)
	{
		pthread_mutex_lock(&phil->left_fork->mutex);
		ft_log(phil->id, phil->waiter, "has taken a fork");
		pthread_mutex_lock(&phil->right_fork->mutex);
		ft_log(phil->id, phil->waiter, "has taken a fork");
		ft_log(phil->id, phil->waiter, "is eating");
		set_lshared(&phil->last_meal_t, get_time());
		usleep(phil->waiter->tte * 1000);
		pthread_mutex_unlock(&phil->left_fork->mutex);
		pthread_mutex_unlock(&phil->right_fork->mutex);
	}
	else
	{
		pthread_mutex_lock(&phil->right_fork->mutex);
		ft_log(phil->id, phil->waiter, "has taken a fork");
		pthread_mutex_lock(&phil->left_fork->mutex);
		ft_log(phil->id, phil->waiter, "has taken a fork");
		ft_log(phil->id, phil->waiter, "is eating");
		set_lshared(&phil->last_meal_t, get_time());
		usleep(phil->waiter->tte * 1000);
		pthread_mutex_unlock(&phil->right_fork->mutex);
		pthread_mutex_unlock(&phil->left_fork->mutex);
	}
	increment_shared(&phil->meal_count);
}

void	*routine(void *arg)
{
	t_philo		*phil;
	t_waiter	*waiter;

	phil = (t_philo *) arg;
	waiter = phil->waiter;
	while (get_lshared(&waiter->start_t) == 0)
		usleep(100);
	// if (phil->id % 2 != 0)
	// 	usleep(100);
	while (get_shared(&waiter->stop) != 1 && get_shared(&phil->eat_enough) != 1)
	{
		go_eat(phil);
		if (get_shared(&waiter->stop) == 1 || get_shared(&phil->eat_enough) == 1)
			break ;
		ft_log(phil->id, waiter, "is thinking");
		if (get_shared(&waiter->stop) == 1 || get_shared(&phil->eat_enough) == 1)
			break ;
		ft_log(phil->id, phil->waiter, "is sleeping");
		usleep(phil->waiter->tts * 1000);
		if (get_shared(&waiter->stop) == 1 || get_shared(&phil->eat_enough) == 1)
			break ;
	}
	return (NULL);
}
