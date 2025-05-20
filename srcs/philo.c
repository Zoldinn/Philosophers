/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:28:21 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/20 12:01:57 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	increment_shared(t_shared *shared)
{
	if (!shared || !shared->created)
		return ;
	pthread_mutex_lock(&shared->mutex);
	shared->data += 1;
	pthread_mutex_unlock(&shared->mutex);
}

void	ft_log(int philo_id, t_waiter *waiter, char *str)
{
	long		t;

	if (!waiter->print.created)
		return ;
	t = get_time() - get_lshared(&waiter->start_t);
	pthread_mutex_lock(&waiter->print.mutex);
	printf("%ld %s%d%s %s\n", t, YELLOW, philo_id, NC, str);
	pthread_mutex_unlock(&waiter->print.mutex);
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
