/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:22:08 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/21 12:11:21 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// print str in red followed by a \n
void	p_r(char *str)
{
	if (!str)
		return ;
	printf("%sERROR%s: %s\n", RED, NC, str);
}

// a big print, when there's not the good count of args when launching philo
void	print_error_arguments(void)
{
	printf("%sError%s : args must be :\n", RED, NC);
	printf("<nb_philos> <time_to_die> <time_to_eat> ");
	printf("<time_to_sleep>\n%s<number_of_times_each_philosopher_eat>", BLUE);
	printf(" (optional)\n%s", NC);
}

int	are_args_numbers(int ac, char **av)
{
	while (--ac > 0)
	{
		if (ft_atoi(av[ac]) <= 0)
			return (1);
	}
	return (0);
}

int	check_nonsense(int ac, char **av)
{
	if (ft_atoi(av[1]) > 200)
		return (1);
	while (--ac > 0)
	{
		if (ft_cmpstr(av[ac], "+0") == 0 || ft_cmpstr(av[ac], "-0") == 0)
			return (1);
		if (ac != 1 && ac != 5 && ft_atoi(av[ac]) < 60)
			return (1);
	}
	return (0);
}

// check all errors about args :
// good count, only nb or signs, no neg values, are coherent
// return 0 if it's ok
int	args_errors_handler(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (print_error_arguments(), 1);
	if (are_args_numbers(ac, av) != 0)
		return (p_r("enter a correct positive number please..."), 1);
	if (check_nonsense(ac, av) != 0)
		return (p_r("don't enter a nonsense please..."), 1);
	return (0);
}
