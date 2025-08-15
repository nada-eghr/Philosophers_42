#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

long long current_time_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int init_data(t_data *data, int ac, char **av)
{
    data->nb_of_philos      = atoi(av[1]);
    data->time_to_die       = atoi(av[2]);
    data->time_to_eat       = atoi(av[3]);
    data->time_to_sleep     = atoi(av[4]);
    if (ac == 6)
        data->nb_time_must_eat = atoi(av[5]);
    else
        data->nb_time_must_eat = -1;
    data->simulation_end    = 0;
    data->start_time        = current_time_ms();


    data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philos);
    if (!data->forks)
    {
        data->philo = NULL;
        return (1);
    }

    // Allocate philosophers
    data->philo = malloc(sizeof(t_philo) * data->nb_of_philos);
    if (!data->philo)
    {
        free(data->forks);
        data->forks = NULL;
        return (1);
    }

    // Initialize mutexes
    for (int i = 0; i < data->nb_of_philos; i++)
        pthread_mutex_init(&data->forks[i], NULL);
    pthread_mutex_init(&data->print_lock, NULL);
    pthread_mutex_init(&data->meal_check, NULL);

    // Initialize philosophers
    for (int i = 0; i < data->nb_of_philos; i++)
    {
        data->philo[i].philo_id         = i + 1;
        data->philo[i].left_fork        = i;
        data->philo[i].right_fork       = (i + 1) % data->nb_of_philos;
        data->philo[i].meal_eaten       = 0;
        data->philo[i].last_meal_eating = data->start_time;
        data->philo[i].data             = data;
    }
    return (0);
}
