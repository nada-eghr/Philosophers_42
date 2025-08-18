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

void *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if(philo->philo_id % 2 == 1) {
        usleep(300);
    }
    while (1)
    { 
        printf("%lld   %d is thinking.\n", current_time_ms() - philo->data->start_time,philo->philo_id);
        pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
        printf("%lld   %d has taken a fork\n", current_time_ms() - philo->data->start_time, philo->philo_id);
        pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
        printf("%lld   %d has taken a fork\n", current_time_ms() - philo->data->start_time, philo->philo_id);

        philo->last_meal_eating = current_time_ms();
        printf("%lld   %d is eating.\n", philo->last_meal_eating - philo->data->start_time ,philo->philo_id);
        philo->meal_eaten++;

        ft_usleep(philo->data->time_to_eat);
        
        pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
        pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);

        printf("%lld   %d is sleeping.\n", current_time_ms() - philo->data->start_time , philo->philo_id);
        usleep(100);
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