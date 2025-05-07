/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:45:16 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/07 19:19:33 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_waiter(t_waiter *waiter, char **av, t_philo **philo, t_fork **fork)
{
	waiter->ttd = ft_atoi(av[2]);
	waiter->tte = ft_atoi(av[3]);
	waiter->tts = ft_atoi(av[4]);
	waiter->mml = -1;
	if (av[5])
		waiter->mml = ft_atoi(av[5]);
	waiter->start = 0;
	waiter->stop = 0;
	waiter->philo = philo;
	waiter->fork = fork;
	return (0);
}

// alloc each forks and give each an id
int	init_forks(t_fork **fork, t_waiter *waiter)
{
	int	i;

	*fork = ft_calloc(sizeof(t_fork), waiter->nbp);
	if (!(*fork))
		return (p_r("forks allocation failed"), 1);
	i = -1;
	while (++i < waiter->nbp)
	{
		(*fork)[i].id = i;
		(*fork)[i].waiter = waiter;
	}
	return (0);
}

// init which fork should be philo's right and left forks,
// give to each philo an id.
int	init_philos(t_philo **philo, t_fork **fork, t_waiter *waiter)
{
	int	i;

	*philo = ft_calloc(sizeof(t_philo), waiter->nbp);
	if (!(*philo))
		return (p_r("philos allocation failed"), 1);
	i = -1;
	while (++i < waiter->nbp)
	{
		if (i == waiter->nbp - 1)
		{
			(*philo)[i].fork[LEFT] = &((*fork)[0]);
			(*philo)[i].fork[RIGHT] = &((*fork)[i]);
		}
		else
		{
			(*philo)[i].fork[LEFT] = &((*fork)[i]);
			(*philo)[i].fork[RIGHT] = &((*fork)[(i + 1) % waiter->nbp]);
		}
		(*philo)[i].id = i;
		(*philo)[i].waiter = waiter;
	}
	return (0);
}

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
