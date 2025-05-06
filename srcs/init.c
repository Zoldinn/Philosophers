/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:45:16 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/06 10:57:03 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/* Init waiter values :
** nbp = nb of philos
** mml = max nb of meal
** starvation = time until they die
** and finally create the mutex for print
**/
static int	init_waiter(t_waiter *waiter, char **av, t_philo **philo, t_fork **fork)
{
	waiter->ttd = ft_atoi(av[2]);
	waiter->tte = ft_atoi(av[3]);
	waiter->tts = ft_atoi(av[4]);
	waiter->mml = -1;
	if (av[5])
		waiter->mml = ft_atoi(av[5]);
	waiter->stop = 0;
	if (pthread_mutex_init(&waiter->print_mutex, NULL) != 0)
		return (print_error("init print mutex failed"), 1);
	if (pthread_create(&waiter->thread, NULL, waiter_routine, waiter) != 0)
		return (print_error("failed create waiter thread"), 1);
	waiter->philo = philo;
	waiter->fork = fork;
	return (0);
}

// Create mutex for each forks and set values like id and taken
// id to recognize and taken for knowing if that fork is already use or not
static int	init_forks(t_fork **fork, t_waiter *waiter)
{
	int	i;

	*fork = ft_calloc(sizeof(t_fork), waiter->nbp);
	if (!(*fork))
		return (print_error("forks allocation failed"), 1);
	i = -1;
	while (++i < waiter->nbp)
	{
		if (pthread_mutex_init(&((*fork)[i].mutex), NULL) != 0)
			return (print_error("init forks mutex failed"), 1);
		(*fork)[i].id = i;
		(*fork)[i].waiter = waiter;
	}
	return (0);
}

// Init the philos and create their threads
// init : which fork should be philo's right and left forks,
// give to each philo an id
static int	init_philos(t_philo **philo, t_fork **fork, t_waiter *waiter)
{
	int	i;

	*philo = ft_calloc(sizeof(t_philo), waiter->nbp);
	if (!(*philo))
		return (print_error("philos allocation failed"), 1);
	i = -1;
	while (++i < waiter->nbp)
	{
		(*philo)[i].id = i;
		(*philo)[i].fork[LEFT] = &((*fork)[i]);
		(*philo)[i].fork[RIGHT] = &((*fork)[(i + 1) % waiter->nbp]);
		(*philo)[i].waiter = waiter;
		if (i == waiter->nbp - 1)
		{
			(*philo)[i].fork[LEFT] = &((*fork)[0]);
			(*philo)[i].fork[RIGHT] = &((*fork)[i]);
		}
	}
	i = -1;
	while (++i < waiter->nbp)
	{
		if (pthread_create(&((*philo)[i].thread), NULL, philo_routine, &(*philo)[i]) != 0)
			return (print_error("failed create philo thread"), 1);
	}
	return (0);
}

// INIT ALL
// the waiter (thread), forks (mutex), philos (threads)
int	init(t_philo **philo, t_waiter *waiter, t_fork **fork, char **av)
{
	if (init_forks(fork, waiter) != 0)
		return (1);
	if (init_philos(philo, fork, waiter) != 0)
		return (1);
	if (init_waiter(waiter, av, philo, fork) != 0)
		return (1);
	return (0);
}

// END ALL
// Clean mutex (forks) and threads (philos and the one for print)
int	joins_and_destroys(t_waiter *waiter, t_philo **philo, t_fork **fork)
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
	}
	if (pthread_mutex_destroy(&waiter->print_mutex) != 0)
		return (print_error("failed detroy print mutex"), 1);
	return (0);
}
