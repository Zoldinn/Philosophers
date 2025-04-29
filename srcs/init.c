/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:45:16 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/29 12:04:37 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_waiter(t_waiter *waiter, char **av)
{
	waiter->nbp = ft_atoi(av[1]);
	waiter->mml = ft_atoi(av[4]);
	waiter->starvation = ft_calloc(sizeof(long), waiter->nbp);
	if (waiter->starvation == NULL)
		return (print_error("starve allocation failed"), 1);
	if (pthread_mutex_init(&waiter->print_mutex, NULL) != 0)
		return (print_error("init print mutex failed"), 1);
	return (0);
}

int	init_forks(t_fork *forks)
{
	if (pthread_mutex_init(&fork[i].mutex, NULL) != 0)
		return (print_error("init forks mutex failed"), 1);
	fork[i].id = i;
	fork[i].taken = 0;
}


int	init_philo(t_philo *philo, t_waiter *waiter, t_fork *fork)
{
	int	i;

	philo = ft_calloc(sizeof(t_philo), waiter->nbp);
	if (!philo)
		return (print_error("philos allocation failed"), 1);
	i = -1;
	while (++i < waiter->nbp)
	{
		
		philo[i].id = i;
		philo[i].fork[LEFT] = &fork[i];
		philo[i].fork[RIGHT] = &fork[(i + 1) % waiter->nbp];
		if (i == waiter->nbp - 1)
		{
			philo[i].fork[LEFT] = &fork[0];
			philo[i].fork[RIGHT] = &fork[i];
		}
	}
	i = -1;
	while (++i < waiter->nbp)
		pthread_create(&philo[i].thread, NULL, philo_routine, &waiter);
	return (0);
}
