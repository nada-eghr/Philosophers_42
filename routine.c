/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:59:11 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/20 20:07:06 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_write(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->write_mutex);
	if (get_simiulation(philo->data) == 1)
	{
		pthread_mutex_unlock(&philo->data->write_mutex);
		return ;
	}
	printf("%d   %d %s", current_time_ms() - philo->data->start_time,
		philo->philo_id, str);
	pthread_mutex_unlock(&philo->data->write_mutex);
}

void	think(t_philo *philo)
{
	(void)philo;
	ft_write(philo, "is thinking\n");
}

void	ft_sleep(t_philo *philo)
{
	ft_write(philo, "is sleeping\n");
	ft_usleep(philo->data->time_to_sleep);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	ft_write(philo, "has taken a fork\n");
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	ft_write(philo, "has taken a fork\n");
	pthread_mutex_lock(&philo->last_meal_eaten_mutex);
	philo->last_meal_eating = current_time_ms();
	pthread_mutex_unlock(&philo->last_meal_eaten_mutex);
	pthread_mutex_lock(&philo->meal_eaten_mutex);
	philo->meal_eaten++;
	pthread_mutex_unlock(&philo->meal_eaten_mutex);
	ft_write(philo, "is eating\n");
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	think(philo);
	if (philo->philo_id % 2 == 1)
	{
		ft_usleep(10);
	}
	while (1)
	{
		if (get_simiulation(philo->data) == 1)
			break ;
		eat(philo);
		ft_sleep(philo);
		usleep(100);
	}
	return (NULL);
}
