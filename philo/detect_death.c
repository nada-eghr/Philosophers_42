/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_death.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:47:34 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/24 14:25:09 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_simulation(t_data *data)
{
	int	value;

	pthread_mutex_lock(&data->simulation_end_mutex);
	value = data->simulation_end;
	pthread_mutex_unlock(&data->simulation_end_mutex);
	return (value);
}

void	check_nb_time_must_eat(t_data *data)
{
	int	j;
	int	counter;

	j = 0;
	counter = 0;
	while (j < data->nb_philos)
	{
		pthread_mutex_lock(&data->philo[j].meal_eaten_mutex);
		if (data->philo[j].meal_eaten >= data->nb_time_must_eat)
		{
			counter++;
		}
		pthread_mutex_unlock(&data->philo[j].meal_eaten_mutex);
		j++;
	}
	if (counter == data->nb_philos)
	{
		pthread_mutex_lock(&data->simulation_end_mutex);
		data->simulation_end = 1;
		pthread_mutex_unlock(&data->simulation_end_mutex);
	}
}

void	*monitor(t_data *data)
{
	int	i;
	int	current_time;

	i = 0;
	while (i < data->nb_philos)
	{
		current_time = current_time_ms();
		pthread_mutex_lock(&data->philo[i].last_meal_eaten_mutex);
		if (current_time - data->philo[i].last_meal_eating > data->time_to_die)
		{
			pthread_mutex_unlock(&data->philo[i].last_meal_eaten_mutex);
			pthread_mutex_lock(&data->simulation_end_mutex);
			data->simulation_end = 1;
			pthread_mutex_unlock(&data->simulation_end_mutex);
			printf("%d   %d died\n", current_time_ms() - data->start_time,
				data->philo[i].philo_id);
			return (NULL);
		}
		pthread_mutex_unlock(&data->philo[i].last_meal_eaten_mutex);
		i++;
	}
	return (NULL);
}

void	*detect_death(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!get_simulation(data))
	{
		monitor(data);
		if (data->nb_time_must_eat > 0)
			check_nb_time_must_eat(data);
		usleep(100);
	}
	return (NULL);
}
