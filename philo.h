/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:26:22 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/21 11:07:09 by lefoffan         ###   ########.fr       */
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
# include <limits.h>

typedef enum e_state
{
	EAT,
	SLEEP,
	TAKE_A_FORK,
	DIE,
	THINK
}	t_state;

typedef struct s_shared
{
	pthread_mutex_t	mutex;
	int				created;
	int				data;
	long			ldata;
}					t_shared;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				created_thread;

	t_shared		meal_count;
	t_shared		last_meal_t;
	t_shared		enough;

	t_shared		*left_fork;
	t_shared		*right_fork;

	struct s_waiter	*waiter;
}					t_philo;

typedef struct s_waiter
{
	int			nbp;
	int			ttd;
	int			tte;
	int			tts;
	int			mml;

	t_shared	start_t;
	t_shared	stop;
	t_shared	print;

	t_philo		*philos;
	t_shared	*forks;

}				t_waiter;

/**========================================================================
 **							PHILO MAIN FUNCTIONS
 *========================================================================**/
int		init(t_waiter *waiter, char **av);
void	destroy_all(t_waiter *waiter);
void	set_shared(t_shared *shared, int value);
void	set_lshared(t_shared *shared, long value);
int		get_shared(t_shared *shared);
long	get_lshared(t_shared *shared);
void	increment_shared(t_shared *shared);
long	get_time(void);
void	ft_log(int philo_id, t_waiter *waiter, char *str);
void	waiter_monitoring(t_waiter *waiter);
void	*routine(void *arg);
long	now(t_waiter *waiter);

/**========================================================================
 **									UTILS
 *========================================================================**/
int		ft_atoi(char *nb);
int		ft_strlen(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_cmpstr(char *s1, char *s2);

/**========================================================================
 **								ERRORS HANDLING
 *========================================================================**/
void	p_r(char *str);
int		args_errors_handler(int ac, char **av);

#endif