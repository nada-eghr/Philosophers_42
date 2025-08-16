/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_death.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:47:34 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/16 18:54:36 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void detect_death(t_philo *philo)
{
    long long current_time;
    int i;

    while (1)
    {
        i = 0;
        while (i < philo->data->nb_philos)
        {
            current_time = current_time_ms();
            if (current_time - philo[i].last_meal_eating > philo->data->time_to_die)
            {
                printf("Philosopher %d has died.\n", philo[i].philo_id);
                exit(0); // or handle death appropriately
            }
            i++;
        }
        usleep(1000); // Check every millisecond
    }
}