/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:28:21 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/30 14:16:53 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int ac, char **av)
{
	t_waiter	waiter;
	t_philo		*philo;
	t_fork		*fork;

	philo = NULL;
	fork = NULL;
	if (args_errors_handler(ac, av) != 0) //todo: ajustements
		return (1);
	if (init(&philo, &waiter, &fork, av) != 0)
		return (1);
	if (joins_and_destroys(&waiter, &philo, &fork) != 0)
		return (1);
	return (0);
}
