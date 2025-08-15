#include "philo.h"

long long current_time_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void init_philosopher(t_philo *philo , t_data *data)
{
    int i = 0;
    while (i < data->nb_of_philos)
    {
        philo->philo_id = i + 1;
        philo->left_fork = i;
        philo->right_fork = (i + 1) % data->nb_of_philos;
        philo->meal_eaten = 0;
        philo->last_meal_eating = data->start_time;
        philo->data = data;

    }
}
int init_data(t_data *data , int ac , char **av)
{
    int i ;

    data->nb_of_philos = atoi(av[1]);
    data->time_to_die = atoi(av[2]);
    data->time_to_eat = atoi(av[3]);
    data->time_to_sleep = atoi(av[4]);
    if ( ac == 6)
        data->nb_time_must_eat = atoi(av[5]);
    else
         data->nb_time_must_eat = -1;

    data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philos);
    if (!data->forks)
    {
        data->philo = NULL;
        return (1);
    }
    data->philo = malloc(sizeof(t_philo) * data->nb_of_philos);
    if (!data->philo)
    {
        free(data->forks);
        data->forks = NULL;
        return 1;
    }
    i = 0;
    while ( i < data->nb_of_philos)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
    data->start_time = current_time_ms();
    init_philosopher(data->philo, data);
    return 0;
}