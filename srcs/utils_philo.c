/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:07:40 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/13 11:40:52 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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

int	ft_log(t_waiter *waiter, t_state state, int philo_id, int waiting)
{
	pthread_mutex_lock(&waiter->print_mutex);
	ft_putnbr(waiter->time);
	write(1, YELLOW, 6);
	write(1, " ", 1);
	ft_putnbr(philo_id);
	write(1, NC, 5);
	if (state == TAKE_A_FORK)
		write(1, " has taken a fork\n", 18);
	else if (state == EAT)
		write(1, " is eating\n", 11);
	else if (state == THINK)
		write(1, " is thinking\n", 13);
	else if (state == SLEEP)
		write(1, " is sleeping\n", 13);
	else if (state == DIE)
		write(1, " died\n", 6);
	else if (state == ENOUGH)
		write(1, " eaten enough\n", 14);
	usleep(waiting);
	pthread_mutex_unlock(&waiter->print_mutex);
	return (0);
}
