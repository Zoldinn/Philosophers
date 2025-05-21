/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:18:50 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/21 12:11:49 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//compare 2 strings by length and char
//0 if same
//1 if different
int	ft_cmpstr(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (0);
	if (ft_strlen(s1) == ft_strlen(s2))
	{
		if (ft_strncmp(s1, s2, ft_strlen(s1)) == 0)
			return (0);
	}
	return (1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 && *s2 && (*s1 == *s2) && n)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char) *s1 - (unsigned char) *s2);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(char *nb)
{
	long	res;
	int		neg;
	int		i;

	i = -1;
	neg = 1;
	res = 0;
	while (nb[++i])
	{
		if (nb[i] == '-')
			neg *= -1;
		else if (nb[i] >= '0' && nb[i] <= '9')
			res = (res * 10) + (nb[i] - '0');
		else if (nb[i] != '+' || (nb[i] == '+' && i != 0))
			return (-1);
	}
	if (res > INT_MAX || res < INT_MIN)
		return (-1);
	return (res * neg);
}
