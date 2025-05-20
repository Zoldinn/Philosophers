/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter_monitoring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:43:06 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/20 11:03:34 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_dead(t_philo *phil, t_waiter *waiter)
{
	long	t;

	t = get_lshared(&phil->last_meal_t) - get_lshared(&waiter->start_t);
	if (t > waiter->ttd)
	{
		set_shared(&waiter->stop, 1);
		ft_log(phil->id, waiter, "died");
		return (1);
	}
	return (0);
}

int	check_eat_count(t_philo *phil, t_waiter *waiter)
{
	if (get_shared(&phil->eat_enough) != 1 && waiter->mml > 0
		&& get_shared(&phil->meal_count) >= waiter->mml)
	{
		set_shared(&waiter->stop, 1);
		set_shared(&phil->eat_enough, 1);
		return (1);
	}
	return (0);
}

void waiter_monitoring(t_waiter *waiter)
{
	t_philo	*phil;
	int		i;
	int		nbp_satisfied;

	nbp_satisfied = 0;
	while (get_shared(&waiter->stop) != 1)
	{
		i = -1;
		while (++i < waiter->nbp)
		{
			phil = &(waiter->philos[i]);
			if (check_dead(phil, waiter) == 1)
				break ;
			if (check_eat_count(phil, waiter) == 1)
				break ;
		}
		usleep(1000);
	}
}
