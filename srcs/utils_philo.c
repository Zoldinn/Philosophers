/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:07:40 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/24 11:38:40 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/* // calloc philos to nb_philos (av[1]) and create the threads
int	init_philos(t_philo *philos, int nbp, void *(ft)(void *), void *args)
{
	int		i;

	if (philos)
		return (1);
	philos = ft_calloc(sizeof(t_philo), (nbp + 1));
	if (!philos)
		return (1);
	i = -1;
	while (++i < nbp)
	{
		if (pthread_create(&philos[i].tid, NULL, ft, args) != 0)
			return (print_error("Thread creation failed"), free(philos), 1);
	}
	return (0);
}

// 0 = ok, otherwise an error occured
int	end_philos(t_philo *philos)
{
	int	i;

	i = -1;
	while (philos[++i].tid)
	{
		if (pthread_join(philos[i].tid, NULL) != 0)
			return (print_error("Thread join failed"), free(philos), 1);
	}
	free(philos);
	return (0);
}
 */