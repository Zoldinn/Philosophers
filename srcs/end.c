/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:07:24 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/19 21:01:38 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void destroy_philos(t_waiter *waiter)
{
	int	i;

	i = -1;
	while (++i < waiter->nbp)
	{
		if (waiter->philos[i].created_thread)
			pthread_join(waiter->philos[i].thread, NULL);
		if (waiter->philos[i].meal_count.created)
			pthread_mutex_destroy(&waiter->philos[i].meal_count.mutex);
		if (waiter->philos[i].last_meal_t.created)
			pthread_mutex_destroy(&waiter->philos[i].last_meal_t.mutex);
		if (waiter->philos[i].eaten_enough.created)
			pthread_mutex_destroy(&waiter->philos[i].eaten_enough.mutex);
	}
	free(waiter->philos);
}

static void	destroy_forks(t_waiter *waiter)
{
	int	i;

	i = -1;
	while (++i < waiter->nbp)
	{
		if (waiter->forks[i].created)
			pthread_mutex_destroy(&waiter->forks[i].mutex);
	}
	free(waiter->forks);
}

void	destroy_all(t_waiter *waiter)
{
	int	i;

	if (waiter->philos)
		destroy_philos(waiter);
	if (waiter->forks)
		destroy_forks(waiter);
	if (waiter->stop.created)
		pthread_mutex_destroy(&waiter->stop.mutex);
	if (waiter->print.created)
		pthread_mutex_destroy(&waiter->print.mutex);
	if (waiter->start_t.created)
		pthread_mutex_destroy(&waiter->start_t.mutex);
}
