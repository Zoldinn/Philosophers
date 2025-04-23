/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:07:40 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/23 16:58:10 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// calloc philos to nb_philos (av[1]) and create the threads
t_philo	*init_philos(int nbp, void *(routine)(void *))
{
	t_philo	*philos;
	int		i;

	philos = ft_calloc(sizeof(t_philo), (nbp + 1));
	if (!philos)
		return (NULL);
	i = -1;
	while (++i < nbp)
	{
		if (pthread_create(&philos[i].tid, NULL, routine, philos) != 0)
			return (print_error("Thread creation failed"), free(philos), NULL);
	}
	return (philos);
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
