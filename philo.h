/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:26:22 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/24 15:27:59 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define NC "\e[0m"
# define RED "\e[31m"
# define BLUE "\e[34m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum e_state
{
	DEAD,
	EATING,
	SLEEPING,
	THINKING,
	TAKE_A_FORK
}	t_state;

typedef struct s_philo
{
	pthread_t	tid;
	// t_state		state;
	// int			starvation_time;
}				t_philo;

/**========================================================================
 **                            UTILS_PHILO
 *========================================================================**/

int		end_philos(t_philo *philos);
int		init_philos(t_philo *philos, int nbp, void *(ft)(void *), void *args);

/**========================================================================
 **                            UTILS_FUNCTIONS
 *========================================================================**/

int		ft_atoi(char *nb);
int		ft_strlen(char *str);
int		ft_cmpstr(char *s1, char *s2);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/**========================================================================
 **                            ERRORS_HANDLING
 *========================================================================**/

void	print_error(char *str);
int		args_errors_handler(int ac, char **av);

#endif