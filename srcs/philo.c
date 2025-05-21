/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:28:21 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/21 12:11:37 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int ac, char **av)
{
	t_waiter	waiter;

	if (args_errors_handler(ac, av) != 0)
		return (1);
	if (init(&waiter, av) != 0)
		return (destroy_all(&waiter), 1);
	set_lshared(&waiter.start_t, get_time());
	waiter_monitoring(&waiter);
	return (destroy_all(&waiter), 0);
}
