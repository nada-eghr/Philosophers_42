/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:22:58 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/24 14:43:17 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	is_positive_number(char *str)
{
	int	i;

	i = 0;
	if (!str[0])
		return (0);
	while (str[i])
	{
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!is_positive_number(args[i]))
			return (0);
		i++;
	}
	return (1);
}

void	free_all(t_data *data)
{
	free(data->forks);
	free(data->philo);
	free(data);
}

void	destroy_mutex(t_data *data)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (j < data->nb_philos)
	{
		pthread_mutex_destroy(&data->philo[j].meal_eaten_mutex);
		pthread_mutex_destroy(&data->philo[j].last_meal_eaten_mutex);
		j++;
	}
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->simulation_end_mutex);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac < 5 || ac > 6)
	{
		printf("wrong number of argumments. \n");
		return (1);
	}
	if (!check_args(av + 1))
	{
		printf("Invalid arguments: only positive numbers allowed.\n");
		return (1);
	}
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (init_data(data, ac, av))
		return (free_all(data), 1);
	data->simulation_end = 0;
	create_philo(data->philo, data);
	detect_death(data);
	destroy_mutex(data);
	free_all(data);
	return (0);
}
