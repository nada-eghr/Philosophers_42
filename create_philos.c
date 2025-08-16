/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:14:30 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/16 19:02:50 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (1)
    { 
        printf("Philosopher %d is thinking.\n", philo->philo_id);
        usleep(100); 
        printf("Philosopher %d is eating.\n", philo->philo_id);
        usleep(100); 
        printf("Philosopher %d is sleeping.\n", philo->philo_id);
        usleep(100);
    }
    return NULL;
}
    
void create_philo(t_philo *philo , t_data *data)
{
    int i;
  
    i = 0;
    while(i < data->nb_philos)
    {
        philo[i].philo_id = i + 1;
        pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
        i++;
    }
    i = 0;
    while ( i < data->nb_philos)
    {
        pthread_join(philo[i].thread, NULL);
        i++;
    }
}