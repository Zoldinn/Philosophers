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

#define LEFT 0
#define RIGHT 1

int nbp = 5;
pthread_mutex_t	print_mutex;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				id;
}					t_fork;

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	t_fork		*fork[2];
}				t_philo;

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;

	pthread_mutex_lock(&philo->fork[LEFT]->mutex);
	pthread_mutex_lock(&print_mutex);
	printf("philo %s%d%s take fork %s%d%s\n", RED, philo->id, NC, RED, philo->fork[LEFT]->id, NC);
	pthread_mutex_unlock(&print_mutex);

	pthread_mutex_lock(&philo->fork[RIGHT]->mutex);
	pthread_mutex_lock(&print_mutex);
	printf("philo %s%d%s take fork %s%d%s\n", RED, philo->id, NC, RED, philo->fork[RIGHT]->id, NC);
	pthread_mutex_unlock(&print_mutex);

	pthread_mutex_lock(&print_mutex);
	printf("philo %s%d%s is eating\n\n", RED, philo->id, NC);
	pthread_mutex_unlock(&print_mutex);

	pthread_mutex_unlock(&philo->fork[RIGHT]->mutex);
	pthread_mutex_unlock(&philo->fork[LEFT]->mutex);

	return (NULL);
}

int	main(void)
{
	t_philo	philo[nbp];
	t_fork	fork[nbp];

	pthread_mutex_init(&print_mutex, NULL);
	for (int i = 0; i < nbp; i++)
	{
		pthread_mutex_init(&fork[i].mutex, NULL);
		fork[i].id = i;
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
