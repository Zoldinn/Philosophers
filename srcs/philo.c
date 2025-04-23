/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:24:57 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/23 10:56:02 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_error_arguments()
{
	printf("\e[31m");
	printf("There must be at least 3 args :\n\n\e[33m");
	printf("<number_philosophers>\n<time_to_die>\n<time_to_eat>\n");
	printf("<time_to_sleep>\n\e[34m<number_of_times_each_philosopher_eat>");
	printf(" (this one is optional)\n\n");
	printf("\e[0m");
}

int	main(int ac, char **av)
{
	if (ac < 4 || ac > 5)
		print_error_arguments();
	(void) av;
	return (0);
}