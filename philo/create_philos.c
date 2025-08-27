/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:14:30 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/24 19:11:18 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int time)
{
	int	start;

	start = current_time_ms();
	while (current_time_ms() - start < time)
		usleep(200);
}

void	*one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	ft_write(philo, "has taken a fork\n");
	ft_usleep(philo->data->time_to_die);
	ft_write(philo, "died\n");
	pthread_mutex_lock(&philo->data->simulation_end_mutex);
	philo->data->simulation_end = 1;
	pthread_mutex_unlock(&philo->data->simulation_end_mutex);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	return (NULL);
}

void	create_philo(t_philo *philo, t_data *data)
{
	int			i;
	pthread_t	death_thread;

	i = 0;
	if (data->nb_philos == 1)
	{
		pthread_create(&philo[0].thread, NULL, &one_philo, &philo[0]);
	}
	else
	{
		while (i < data->nb_philos)
		{
			philo[i].philo_id = i + 1;
			pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
			i++;
		}
	}
	pthread_create(&death_thread, NULL, detect_death, data);
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	pthread_join(death_thread, NULL);
}
