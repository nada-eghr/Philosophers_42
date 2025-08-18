/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:14:30 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/17 19:26:20 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_usleep(int time)
{
    int	start;

	start = current_time_ms();
	while (current_time_ms() - start < time)
		usleep(200);
}

void think(t_philo *philo)
{
    (void) philo;
    printf("%d   %d is thinking.\n", current_time_ms() - philo->data->start_time,philo->philo_id);
}

void ft_sleep(t_philo *philo)
{
    printf("%d   %d is sleeping.\n", current_time_ms() - philo->data->start_time , philo->philo_id);
    ft_usleep(philo->data->time_to_sleep);
}

void ft_write() {
    // if one of the philos died return

    //lock print mutex
    // printf();
    //unlock print mutex

}

void eat(t_philo *philo) 
{
    pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
    ft_write(philo, "message");
    printf("%d   %d has taken a fork\n", current_time_ms() - philo->data->start_time, philo->philo_id);
    pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
    printf("%d   %d has taken a fork\n", current_time_ms() - philo->data->start_time, philo->philo_id);

    philo->last_meal_eating = current_time_ms();
    printf("%lld   %d is eating.\n", philo->last_meal_eating - philo->data->start_time ,philo->philo_id);

    //lock
    philo->meal_eaten++;
    //unlock

    ft_usleep(philo->data->time_to_eat);
    
    pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
    pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}

void *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    think(philo);
    if(philo->philo_id % 2 == 1) {
        ft_usleep(philo->data->time_to_eat / 2);
    }
    while (1)
    { 
        eat(philo);
        ft_sleep(philo);
        usleep(200);
    }
    return NULL;
}
    


void create_philo(t_philo *philo , t_data *data)
{
    int i;
    pthread_t death_thread;
    i = 0;
    while(i < data->nb_philos)
    {
        philo[i].philo_id = i + 1;
        pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
        i++;
    }
    pthread_create(&death_thread, NULL, detect_death, data);
    i = 0;
    while ( i < data->nb_philos)
    {
        pthread_join(philo[i].thread, NULL);
        i++;
    }
    pthread_join(death_thread, NULL);
}