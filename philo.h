/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:26:22 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/29 11:46:12 by lefoffan         ###   ########.fr       */
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

# define LEFT 0
# define RIGHT 1

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				id;
	int				taken;
}					t_fork;

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	t_fork		*fork[2];
	long		last_meal;
	long		meal_count;
}				t_philo;

typedef struct s_waiter
{
	int				nbp;
	int				mml;
	int				die;
	long			*starvation;
	t_philo			*philo;
	t_fork			*fork;
	pthread_mutex_t	print_mutex;
}					t_waiter;

/**========================================================================
 **                       PHILO MAIN FUNCTIONS
 *========================================================================**/

long	get_time();
void	*philo_routine(void *arg);

/**========================================================================
 **                            UTILS PHILO
 *========================================================================**/

int		init_waiter(t_waiter *waiter, char **av);

/**========================================================================
 **                            UTILS PHILO
 *========================================================================**/

int		end_philos(t_philo *philos);
int		init_philos(t_philo *philos, int nbp, void *(ft)(void *), void *args);

/**========================================================================
 **                          UTILS FUNCTIONS
 *========================================================================**/

int		ft_atoi(char *nb);
int		ft_strlen(char *str);
int		ft_cmpstr(char *s1, char *s2);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/**========================================================================
 **                           ERRORS HANDLING
 *========================================================================**/

void	print_error(char *str);
int		args_errors_handler(int ac, char **av);

#endif