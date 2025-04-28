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

#include "srcs/utils_func.c"

#define LEFT 0
#define RIGHT 1

int nbp = 5;
pthread_mutex_t	print_mutex;

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
	int		nbp;
	long	*starvation;
	int		mml;

}			t_waiter;


long	get_time()
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;

	pthread_mutex_lock(&philo->fork[LEFT]->mutex);
	philo->fork[LEFT]->taken = 1;
	pthread_mutex_lock(&print_mutex);
	printf("philo %s%d%s take fork %s%d%s\n", RED, philo->id, NC, RED, philo->fork[LEFT]->id, NC);
	pthread_mutex_unlock(&print_mutex);

	pthread_mutex_lock(&philo->fork[RIGHT]->mutex);
	philo->fork[RIGHT]->taken = 1;
	pthread_mutex_lock(&print_mutex);
	printf("philo %s%d%s take fork %s%d%s\n", RED, philo->id, NC, RED, philo->fork[RIGHT]->id, NC);
	pthread_mutex_unlock(&print_mutex);

	pthread_mutex_lock(&print_mutex);
	if (philo->fork[LEFT]->taken == 1 && philo->fork[RIGHT]->taken == 1)
		printf("philo %s%d%s is eating\n\n", RED, philo->id, NC);
	pthread_mutex_unlock(&print_mutex);

	philo->fork[RIGHT]->taken = 0;
	pthread_mutex_unlock(&philo->fork[RIGHT]->mutex);
	philo->fork[LEFT]->taken = 0;
	pthread_mutex_unlock(&philo->fork[LEFT]->mutex);

	return (NULL);
}

int	main(int ac, char **av)
{
	t_philo		*philo;
	t_fork		*fork;
	t_waiter	waiter;

	if (ac != 4 || ac != 5)
		return (1);
	waiter.nbp = ft_atoi(av[1]);
	waiter.mml = ft_atoi(av[4]);
	waiter.starvation = ft_calloc(sizeof(long), waiter.nbp);
	if (waiter.starvation == NULL)
		return (print_error("allocation\n"), 1);
	philo = ft_calloc(sizeof(t_philo), waiter.nbp);
	if (!philo)
		return (print_error("allocation\n"), 1);
	pthread_mutex_init(&print_mutex, NULL);
	for (int i = 0; i < nbp; i++)
	{
		pthread_mutex_init(&fork[i].mutex, NULL);
		fork[i].id = i;
		fork[i].taken = 0;
		philo[i].id = i;
		philo[i].fork[LEFT] = &fork[i];
		philo[i].fork[RIGHT] = &fork[(i + 1) % nbp];
		if (i == nbp - 1)
		{
			philo[i].fork[LEFT] = &fork[0];
			philo[i].fork[RIGHT] = &fork[i];
		}

	}
	for (int i = 0; i < nbp; i++)
		pthread_create(&philo[i].thread, NULL, routine, &philo[i]);
	for (int i = 0; i < nbp; i++)
		pthread_join(philo[i].thread, NULL);
	for (int i = 0; i < nbp; i++)
		pthread_mutex_destroy(&fork[i].mutex);
	pthread_mutex_destroy(&print_mutex);
	return (0);
}
