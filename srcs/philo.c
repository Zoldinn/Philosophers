/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:28:21 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/09 11:18:52 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// last meal 			: avant de manger
// commencer starvation : juste apres manger
// 
// doivent tous commencer en meme temps
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (!philo->waiter->stop)
	{
		
	}
	return (NULL);
}

int	waiter_monitoring(t_waiter *waiter)
{
	t_philo	**philos;
	t_philo	*philo;
	int		i;

	waiter->time = get_time();
	philos = waiter->philo;
	i = -1;
	while (++i < waiter->nbp)
	{
		philo = &((*philos)[i]);
		if (pthread_mutex_lock(&philo->last_meal_mutex) != 0)
			return (p_r("Failed lock mutex last_meal"), 1);
		if ((waiter->mml && philo->meal_count >= waiter->mml)
			|| (philo->last_meal + waiter->tte >= waiter->ttd))
		{
			waiter->stop = 1;
			return (0);
		}
		if (pthread_mutex_unlock(&philo->last_meal_mutex) != 0)
			return (p_r("Failed lock mutex last_meal"), 1);
	}
	return (0);
}

//todo: reaplce printf par write 
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
	{
		if (waiter_monitoring(&waiter) != 0)
			return (1);
	}
	if (end(&waiter, &philo, &fork) != 0) //? ameliorations?
		return (1);
	free(philo);
	free(fork);
	return (0);
}
