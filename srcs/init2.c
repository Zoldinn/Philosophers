/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:54:22 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/07 16:46:38 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	create_all_mutex(t_waiter *waiter)
{
	int		i;
	t_philo	**philo;
	t_fork	**fork;

	philo = waiter->philo;
	fork = waiter->fork;
	i = -1;
	while (++i < waiter->nbp)
	{
		if (pthread_mutex_init(&((*fork)[i].mutex), NULL) != 0)
			return (print_error("init forks mutex failed"), 1);
		if (pthread_mutex_init(&((*philo)[i].last_meal_mutex), NULL) != 0)
			return (print_error("failed init meal mutex"), 1);
		if (pthread_mutex_init(&waiter->print_mutex, NULL) != 0)
			return (print_error("failed init print mutex"), 1);
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
			return (print_error("failed create philo thread"), 1);
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
	while (++i < waiter->nbp)
	{
		if (pthread_join((*philo)[i].thread, NULL) != 0)
			return (print_error("failed joining philo's threads"), 1);
	}
	i = -1;
	while (++i < waiter->nbp)
	{
		if (pthread_mutex_destroy(&((*fork)[i].mutex)) != 0)
			return (print_error("failed to destroy fork's mutex"), 1);
		if (pthread_mutex_destroy(&((*philo)[i].last_meal_mutex)) != 0)
			return (print_error("failed to destroy fork's mutex"), 1);
	}
	if (pthread_mutex_destroy(&waiter->print_mutex) != 0)
		return (print_error("failed detroy print mutex"), 1);
	return (0);
}
