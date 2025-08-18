/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_death.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:47:34 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/17 19:21:52 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void *detect_death(void *arg)
{
    long long current_time;
    t_data *data;
    data = (t_data *)arg;
    int i;

    while (!data->simulation_end)
    {
        i = 0;
        while (i < data->nb_philos)
        {
            current_time = current_time_ms();
            if (current_time - data->philo[i].last_meal_eating > data->time_to_die)
            {
               printf("%lld   %d is died\n",
                       current_time_ms() - data->start_time,
                       data->philo[i].philo_id);
                data->simulation_end = 1;
                return NULL;
            }
            i++;
        }
        usleep(1000); // Check every millisecond
    }
    return NULL;
}
