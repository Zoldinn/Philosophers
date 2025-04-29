/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .philo(old).c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:24:57 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/29 11:32:37 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int counter = 0;
pthread_mutex_t	mutex;

void	*routine(void *args)
{
	int	tid;

	tid = *(int *) args;
	if (pthread_mutex_lock(&mutex) != 0)
		return (NULL);
	for (int i = 0; i < 1000000; i++)
		++counter;
	printf("counter = %d\n", counter);
	if (pthread_mutex_unlock(&mutex) != 0)
		return (NULL);
	return (NULL);
}

int	main(int ac, char **av)
{
	// t_philo	*philos;
	pthread_t	*threads;
	int			*tids;
	int			nt;

	if (args_errors_handler(ac, av) != 0)
		return (1);
	
	if (pthread_mutex_init(&mutex, NULL) != 0)
		return (print_error("failed init mutex"), 1);

	nt = ft_atoi(av[1]);
	threads = ft_calloc(sizeof(pthread_t), nt);
	if (!threads)
		return (print_error("ft_calloc failed"), 1);
	tids = ft_calloc(sizeof(int), nt);
	if (!tids)
		return (print_error("ft_calloc failed"), 1);

	for (int i = 0; i < nt; i++)
	{
		tids[i] = i + 1;
		if (pthread_create(&threads[i], NULL, routine, &tids[i]) != 0)
			return (print_error("Thread creation failed"), free(threads), free(tids), 1);
	}

	for (int i = 0; i < nt; i++)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (print_error("Thread join failed"), free(threads), free(tids), 1);
	}

	free(threads);
	free(tids);

	if (pthread_mutex_destroy(&mutex) != 0)
		return (print_error("destroying mutex failed"), 1);
	// init_philos(philos, ft_atoi(av[1]), routine, philos);
	// if (!philos)
	// 	return (1);
	// if (end_philos(philos) != 0)
	// 	return (1);
	return (0);
}