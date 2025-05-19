/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:28:21 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/19 20:50:22 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>

void	ft_log(int philo_id, t_waiter *waiter, char *str)
{
	t_shared	*print;
	t_shared	*start_t;

	print = &waiter->print;
	start_t = &waiter->start_t;
	if (!print || !print->created)
		return ;
	pthread_mutex_lock(&start_t->mutex);
	printf("%ld %d ", get_time() - start_t->ldata, philo_id);
	pthread_mutex_lock(&print->mutex);
	printf("%s\n", str);
	pthread_mutex_unlock(&start_t->mutex);
	pthread_mutex_unlock(&print->mutex);
}

int	main(int ac, char **av)
{
	t_waiter	waiter;

	if (args_errors_handler(ac, av) != 0) // Ajustements : faire un tab int
		return (1);
	if (init(&waiter, av) != 0)
		return (destroy_all(&waiter), 1);
	waiter_monitoring(&waiter);

	
	return (destroy_all(&waiter), 0);
}
