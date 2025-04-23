/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:24:57 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/23 17:19:40 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/* void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	printf("thread [%ld] : %s\n", philo->tid, (char *) philo->data);
	return (NULL);
} */

int	main(int ac, char **av)
{
	// t_philo	*philos;

	if (args_errors_handler(ac, av) != 0)
		return (1);
	// philos = init_philos(ft_atoi(av[1]), routine);
	// if (!philos)
	// 	return (1);
	// if (end_philos(philos) != 0)
	// 	return (1);
	return (0);
}