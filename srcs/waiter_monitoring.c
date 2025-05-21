/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter_monitoring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:43:06 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/21 12:12:26 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_dead(t_philo *phil, t_waiter *waiter)
{
	long	t;

	t = now(waiter) - get_lshared(&phil->last_meal_t);
	if (t > waiter->ttd)
	{
		set_shared(&waiter->stop, 1);
		ft_log(phil->id, waiter, "\e[31mdied\e[0m");
		return (1);
	}
	return (0);
}

int	check_eat_count(t_philo *phil, t_waiter *waiter, int *nbp_satisfied)
{
	if (waiter->mml > 0 && get_shared(&phil->meal_count) >= waiter->mml)
	{
		if (get_shared(&phil->enough) != 1)
		{
			set_shared(&phil->enough, 1);
			*nbp_satisfied += 1;
		}
		if (*nbp_satisfied == waiter->nbp)
			return (set_shared(&waiter->stop, 1), 1);
	}
	return (0);
}

void	waiter_monitoring(t_waiter *waiter)
{
	t_philo	*phil;
	int		i;
	int		nbp_satisfied;

	nbp_satisfied = 0;
	while (get_lshared(&waiter->start_t) == 0)
		usleep(1000);
	while (get_shared(&waiter->stop) != 1)
	{
		i = -1;
		while (++i < waiter->nbp)
		{
			phil = &(waiter->philos[i]);
			if (check_dead(phil, waiter) == 1)
				break ;
			if (check_eat_count(phil, waiter, &nbp_satisfied) == 1)
				break ;
		}
		usleep(6000);
	}
}
