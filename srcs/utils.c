/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:18:50 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/23 11:57:55 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(char *str)
{
	if (!str)
		return ;
	printf("%sError : %s\n%s", RED, str, NC);
}

int	ft_atoi(char *nb)
{
	int	i;
	int	res;
	int	neg;

	i = -1;
	neg = 1;
	res = 0;
	while (nb[++i])
	{
		if (nb[i] == '-')
			neg *= -1;
		else if (nb[i] >= '0' && nb[i] <= '9')
			res = (res * 10) + (nb[i] - '0');
	}
	return (res * neg);
}
