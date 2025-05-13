/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:28:21 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/13 11:44:57 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	waiter_monitoring(t_waiter *waiter, t_philo **philos)
{
	t_philo	*philo;
	int		i;

	waiter->time = waiter->start_time - get_time();
	i = -1;
	while (++i < waiter->nbp && waiter->stop != 1)
	{
		philo = &((*philos)[i]);
		pthread_mutex_lock(&philo->last_meal_mutex);
		if (waiter->mml && philo->meal_count >= waiter->mml)
		{
			ft_log(waiter, ENOUGH, philo->id, 0);
			waiter->stop = 1;
		}
		else if (philo->last_meal + waiter->tte >= waiter->ttd)
		{
			ft_log(waiter, DIE, philo->id, 0);
			waiter->stop = 1;
		}
		pthread_mutex_unlock(&philo->last_meal_mutex);
	}
}

int	main(int ac, char **av)
{
	t_waiter	waiter;
	t_philo		*philo;
	t_fork		*fork;

	philo = NULL;
	fork = NULL;
	if (args_errors_handler(ac, av) != 0) //todo: ajustements
		return (1);
	waiter.nbp = ft_atoi(av[1]);
	if (init(&philo, &waiter, &fork, av) != 0 || start(&waiter) != 0)
		return (1);
	while (!waiter.stop)
		waiter_monitoring(&waiter, waiter.philo);
	if (end(&waiter, &philo, &fork) != 0)
		return (1);
	free(philo);
	free(fork);
	return (0);
}
