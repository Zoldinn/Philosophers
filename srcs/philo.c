/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:28:21 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/13 18:20:42 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_stop(t_waiter *waiter)
{
		pthread_mutex_lock(&waiter->mutex);
		if (waiter->stop == 1)
		{
			pthread_mutex_unlock(&waiter->mutex);
			return (1);
		}
		pthread_mutex_unlock(&waiter->mutex);
		return (0);
}

void	stop(t_waiter *waiter)
{
	pthread_mutex_lock(&waiter->mutex);
	waiter->stop = 1;
	pthread_mutex_unlock(&waiter->mutex);
}

void	waiter_monitoring(t_waiter *waiter, t_philo **philos)
{
	t_philo	*philo;
	int		i;

	wait_start(waiter);
	while (1)
	{
		if (check_stop(waiter) == 1)
			break ;
		i = -1;
		while (++i < waiter->nbp)
		{
			philo = &((*philos)[i]);
			pthread_mutex_lock(&philo->mutex);
			waiter->time = get_time() - waiter->start_time;
			if (waiter->mml && philo->eaten_enough != 1
				&& philo->meal_count >= waiter->mml)
			{
				pthread_mutex_lock(&philo->mutex);
				waiter->nb_eaten_enough += 1;
				if (waiter->nb_eaten_enough == waiter->nbp)
					stop(waiter);
				pthread_mutex_unlock(&philo->mutex);
			}
			else if (waiter->time - philo->last_meal > waiter->ttd)
			{
				ft_log(waiter, DIE, philo->id, 0);
				stop(waiter);
				break ;
			}
			pthread_mutex_unlock(&philo->mutex);
			usleep(100);
		}
	}
}

//* refaire en simplifiant/prevoyant
int	main(int ac, char **av)
{
	t_waiter	waiter;
	t_philo		*philo;
	t_fork		*fork;

	philo = NULL;
	fork = NULL;
	if (args_errors_handler(ac, av) != 0) //ajustements : faire un tab int
		return (1);

	waiter.nbp = ft_atoi(av[1]);
	if (init(&philo, &waiter, &fork, av) != 0 || start(&waiter) != 0)
		return (1);

	waiter_monitoring(&waiter, waiter.philo);

	if (end(&waiter, &philo, &fork) != 0)
		return (1);

	free(philo);
	free(fork);
	return (0);
}
