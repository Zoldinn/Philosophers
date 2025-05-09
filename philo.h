/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:26:22 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/09 18:43:40 by lefoffan         ###   ########.fr       */
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

typedef enum e_state
{
	TAKE_A_FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_state;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				created_m;
	int				id;
	struct s_waiter	*waiter;
}					t_fork;

typedef struct s_philo
{
	int				id;
	t_fork			*fork[2];
	pthread_t		thread;
	int				created_t;
	int				is_dead;
	long			meal_count;
	long			last_meal;
	pthread_mutex_t	last_meal_mutex;
	int				created_m;
	struct s_waiter	*waiter;
}					t_philo;

// nbp : nb philo
// ttd : time to die
// tte : time to eat
// tts : time to sleep
// mml : max meal / max amount of meal
typedef struct s_waiter
{
	int				nbp;
	int				ttd;
	int				tte;
	int				tts;
	int				mml;
	int				start;
	pthread_mutex_t	start_mutex;
	int				created_m_s;
	int				stop;
	long			time;
	t_philo			**philo;
	t_fork			**fork;
	pthread_mutex_t	print_mutex;
	int				created_m_p;
}					t_waiter;

/**========================================================================
 **							PHILO MAIN FUNCTIONS
 *========================================================================**/

int		init(t_philo **philo, t_waiter *waiter, t_fork **fork, char **av);
int		start(t_waiter *waiter);
int		end(t_waiter *waiter, t_philo **philo, t_fork **fork);
void	*routine(void *arg);
long	get_time();
int		log(t_waiter *waiter, t_state state, int philo_id, int waiting);

/**========================================================================
 **							UTILS
 *========================================================================**/

int		ft_atoi(char *nb);
int		ft_strlen(char *str);
int		ft_cmpstr(char *s1, char *s2);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putnbr(long nb);

/**========================================================================
 **							ERRORS HANDLING
 *========================================================================**/

void	p_r(char *str);
int		args_errors_handler(int ac, char **av);

#endif