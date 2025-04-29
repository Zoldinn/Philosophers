/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:28:21 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/29 12:04:39 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int ac, char **av)
{
	t_waiter	waiter;
	t_philo		*philo;
	t_fork		*fork;

	if (args_errors_handler(ac, av) != 0) //todo: revoir car doit accepter ou reagir plus precis
		return (1);

	if (init_waiter(&waiter, av) != 0)
		return (1);



	for (int i = 0; i < waiter.nbp; i++)
		pthread_join(philo[i].thread, NULL);

	for (int i = 0; i < waiter.nbp; i++)
		pthread_mutex_destroy(&fork[i].mutex);

	pthread_mutex_destroy(&waiter.print_mutex);

	return (0);
}
