/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:26:22 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/30 16:24:14 by lefoffan         ###   ########.fr       */
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
	struct s_waiter	*waiter;
}					t_fork;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	t_fork			*fork[2];
	long			last_meal;
	long			meal_count;
	struct s_waiter	*waiter;
}					t_philo;

typedef struct s_waiter
{
	pthread_t		thread;
	int				nbp;
	int				ttd;
	int				tte;
	int				tts;
	int				mml;
	int				stop;
	t_philo			**philo;
	t_fork			**fork;
	pthread_mutex_t	print_mutex;
}					t_waiter;

/**========================================================================
 **							PHILO MAIN FUNCTIONS
 *========================================================================**/

void	*philo_routine(void *arg);
void	*waiter_routine(void *arg)
int		init(t_philo **philo, t_waiter *waiter, t_fork **fork, char **av);
int		joins_and_destroys(t_waiter *waiter, t_philo **philo, t_fork **fork);

/**========================================================================
 **							UTILS
 *========================================================================**/

long	get_time();
int		ft_atoi(char *nb);
int		ft_strlen(char *str);
int		ft_cmpstr(char *s1, char *s2);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/**========================================================================
 **							ERRORS HANDLING
 *========================================================================**/

void	print_error(char *str);
int		args_errors_handler(int ac, char **av);

#endif