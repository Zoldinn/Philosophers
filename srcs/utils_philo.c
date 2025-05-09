/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:07:40 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/09 12:24:56 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// Return a long bc time is a from 1970 in sec so it's very big
// return the time is ms (milisec)
// to have actual time (time start - actual time)
long	get_time()
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void	ft_putnbr(long nb)
{
	char	res;

	if (nb < 0)
	{
		write(1, "-", 1);
		nb = -nb;
	}
	if (nb > 9)
		ft_putnbr(nb / 10);
	res = (nb % 10) + '0';
	write(1, &res, 1);
}

int	log(t_waiter *waiter, t_state state, t_philo philo, t_fork fork)
{
	//? mutex?
	if (state == TAKE_A_FORK)
	{
		write(1, YELLOW, 6);
		ft_putnbr(philo.id);
		write(1, NC, 5);
		
	}
}
