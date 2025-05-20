/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:45:16 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/20 17:24:31 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	init_shared(t_shared *shared, int data, long ldata)
{
	if (pthread_mutex_init(&shared->mutex, NULL) != 0)
	{
		shared->created = 0;
		p_r("Failed init mutex");
		return (1);
	}
	shared->created = 1;
	shared->data = data;
	shared->ldata = ldata;
	return (0);
}

static int	init_forks(t_waiter *waiter)
{
	int		i;
	t_philo	*philo;

	waiter->forks = malloc(sizeof(t_shared) * waiter->nbp);
	if (waiter->forks == NULL)
		return (p_r("Failed to allocate forks"), 1);
	i = -1;
	while (++i < waiter->nbp)
	{
		if (init_shared(&waiter->forks[i], 0, 0) != 0)
			return (1);
	}
	while (--i >= 0)
	{
		philo = &waiter->philos[i];
		philo->left_fork = &waiter->forks[i];
		if (i == 0)
			philo->right_fork = &waiter->forks[waiter->nbp - 1];
		else
			philo->right_fork = &waiter->forks[i - 1];
	}
	return (0);
}

static int	init_philos(t_waiter *waiter)
{
	t_philo	*philo;
	int		i;

	waiter->philos = malloc(sizeof(t_philo) * waiter->nbp);
	if (waiter->philos == NULL)
		return (p_r("Allocation for philos failed"), 1);
	i = -1;
	while (++i < waiter->nbp)
	{
		philo = &waiter->philos[i];
		philo->id = i + 1;
		philo->waiter = waiter;
		if (init_shared(&philo->meal_count, 0, 0) != 0
			|| init_shared(&philo->last_meal_t, 0, 0) != 0
			|| init_shared(&philo->enough, 0, 0) != 0)
			return (1);
	}
	return (0);
}

static int	start_threads(t_waiter *waiter)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < waiter->nbp)
	{
		philo = &waiter->philos[i];
		if (pthread_create(&philo->thread, NULL, routine, philo) != 0)
		{
			philo->created_thread = 0;
			return (p_r("Failed create thread"), 1);
		}
		philo->created_thread = 1;
	}
	return (0);
}

int	init(t_waiter *waiter, char **av)
{
	waiter->nbp = ft_atoi(av[1]);
	waiter->ttd = ft_atoi(av[2]);
	waiter->tte = ft_atoi(av[3]);
	waiter->tts = ft_atoi(av[4]);
	waiter->mml = -1;
	if (av[5])
		waiter->mml = ft_atoi(av[5]);
	if (init_shared(&waiter->stop, 0, 0) != 0
		|| init_shared(&waiter->print, 0, 0) != 0
		|| init_shared(&waiter->start_t, 0, 0) != 0
		|| init_philos(waiter) != 0
		|| init_forks(waiter) != 0
		|| start_threads(waiter) != 0)
		return (1);
	return (0);
}
