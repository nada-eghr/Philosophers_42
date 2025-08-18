/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 12:21:53 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/17 19:30:51 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	init_philosopher(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		philo[i].philo_id = i + 1;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % data->nb_philos;
		philo[i].meal_eaten = 0;
		philo[i].last_meal_eating = data->start_time;
		philo[i].data = data;
        i++;
	}
}
int init_args(t_data *data, int ac, char **av)
{
    data->nb_philos = atoi(av[1]);
    if (data->nb_philos <= 0 || data->nb_philos > 200)
    {
        printf("Invalid number of philosophers\n");
        return (1);
    }
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[3]);
	data->time_to_sleep = atoi(av[4]);
	if (ac == 6)
		data->nb_time_must_eat = atoi(av[5]);
	else
		data->nb_time_must_eat = -1;
	if (data->time_to_die <= 0|| data->time_to_eat <= 0 
		|| data->time_to_sleep <= 0 || (ac == 6
			&& data->nb_time_must_eat <= 0))
    {
        printf("all arguments must be positive numbers\n");
        return (1);
    }
    return (0);
}

int	init_data(t_data *data, int ac, char **av)
{
	int	i;
    if (init_args(data, ac, av))
	{
        return (1);

	}

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->forks)
    {
        data->philo = NULL;
		return (1);
    }
	data->philo = malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->philo)
    {
        free(data->forks);
        data->forks = NULL;
		return (1);
    }
	i = 0;
	while (i < data->nb_philos)
    {
		pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
	data->simulation_end = 0;
	data->start_time = current_time_ms();
	init_philosopher(data->philo, data);
	return (0);
}
