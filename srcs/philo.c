/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:24:57 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/23 11:59:17 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_error_arguments()
{
	printf("%sThere must be at least 3 args :\n\n", RED);
	printf("%s<number_philosophers>\n<time_to_die>\n<time_to_eat>\n", YELLOW);
	printf("<time_to_sleep>\n%s<number_of_times_each_philosopher_eat>", BLUE);
	printf(" (this one is optional)\n\n%s", NC);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	printf("thread [%ld] : %s\n", philo->tid, (char *) philo->data);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	if (ac < 4 || ac > 5)
		print_error_arguments();
	(void) av;
	philo = malloc(sizeof(t_philo) * (ft_atoi(av[1]) + 1));
	if (!philo)
		return (1);
	
	// if (pthread_create(&philo.tid, NULL, routine, &philo) != 0)
	// 	return (print_error("Thread creation failed"), 1);
	// if (pthread_join(philo.tid, NULL) != 0)
	// 	return (print_error("Thread join failed"), 1);
	return (0);
}