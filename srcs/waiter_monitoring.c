/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter_monitoring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:43:06 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/19 21:02:33 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int waiter_monitoring(t_waiter *waiter)
{
	t_philo	*phil;
	long	t;
	int		i;
	int		nbp_satisfied;

	nbp_satisfied = 0;
	while (get_shared(&waiter->stop) != 1)
	{
		i = -1;
		while (++i < waiter->nbp)
		{
			phil = &(waiter->philos[i]);
			t = get_lshared(&phil->last_meal_t) - get_lshared(&waiter->start_t);
			if (t > waiter->ttd)
			{
				set_shared(&waiter->stop, 1);
				ft_log(phil->id, waiter, "died");
				break ;
			}
			if (phil->meal_count) // just added shared eaten enough
		}
	}
}
