/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:54:22 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/07 19:23:29 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	create_all_mutex(t_waiter *waiter)
{
	int		i;
	t_philo	**philos;
	t_fork	**forks;
	t_philo	*philo;
	t_fork	*fork;

	philo = waiter->philo;
	fork = waiter->fork;
	i = -1;
	while (++i < waiter->nbp)
	{
		philo = &((*philos)[i]);
		fork = &((*forks)[i]);
		if (pthread_mutex_init(&fork->mutex, NULL) != 0)
			return (p_r("init forks mutex failed"), fork->created_m = 0, 1);
		if (pthread_mutex_init(&philo->last_meal_mutex, NULL) != 0)
			return (p_r("failed init meal mutex"), philo->created_m = 0, 1);
		if (pthread_mutex_init(&waiter->print_mutex, NULL) != 0)
			return (p_r("failed init print mutex"), waiter->created_m = 0, 1);
		fork->created_m = 1;
		philo->created_m = 1;
		waiter->created_m = 1;
	}
	return (0);
}

int	start_philos_threads(t_waiter *waiter)
{
	int		i;
	t_philo	**philos;
	t_philo	*philo;

	philos = waiter->philo;
	i = -1;
	while (++i < waiter->nbp)
	{
		philo = &((*philos)[i]);
		if (pthread_create(philo->thread, NULL, routine, philo) != 0)
			return (p_r("failed create philo thread"), philo->created_t = 0, 1);
		philo->created_t = 1;
	}
	return (0);
}

// Create all mutex and start philos threads
int	start(t_waiter *waiter)
{
	if (create_all_mutex(waiter) != 0)
		return (1);
	if (start_philos_threads(waiter) != 0)
		return (1);
	return (0);
}

// Do joins and destroys to clean mutex (forks)
// and threads (philos and the one for print)
int	end(t_waiter *waiter, t_philo **philo, t_fork **fork)
{
	int	i;

	i = -1;
	while (++i < waiter->nbp && (*philo)[i].created_t)
	{
		if (pthread_join((*philo)[i].thread, NULL) != 0)
			return (p_r("failed joining philo's threads"), 1);
	}
	i = -1;
	while (++i < waiter->nbp && (*fork)[i].created_m )
	{
		if (pthread_mutex_destroy(&((*fork)[i].mutex)) != 0)
			return (p_r("failed to destroy fork's mutex"), 1);
	}
	i = -1;
	while (++i < waiter->nbp && (*philo)[i].created_m)
	{
		if (pthread_mutex_destroy(&((*philo)[i].last_meal_mutex)) != 0)
			return (p_r("failed to destroy fork's mutex"), 1);
	}
	if (waiter->created_m && pthread_mutex_destroy(&waiter->print_mutex) != 0)
		return (p_r("failed detroy print mutex"), 1);
	return (0);
}
