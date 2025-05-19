/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:26:22 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/19 18:15:16 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define NC "\e[0m"
# define RED "\e[31m"
# define BLUE "\e[34m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"

# include <bits/pthreadtypes.h>
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
	t_shared		last_meal_time;

	t_shared		*left_fork;
	t_shared		*right_fork;
}					t_philo;

typedef struct s_waiter
{
	int			nbp;
	int			ttd;
	int			tte;
	int			tts;
	int			mml;

	long		start_time;
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

void	*routine(void *arg);
long	get_time();
int		ft_log(t_waiter *waiter, t_state state, int philo_id, int waiting);
void	wait_start(t_waiter *waiter);

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