/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:22:58 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/20 20:12:01 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	ll(void)
{
	system("leaks -q philo");
}

void	free_all(t_data *data)
{
	free(data->forks);
	free(data->philo);
	free(data);
}

int	main(int ac, char **av)
{
	t_data	*data;
    atexit(ll);
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
	{
		free_all(data);
		return (1);
	}
	data->simulation_end = 0;
	create_philo(data->philo, data);
	detect_death(data);
	free_all(data);
	return (0);
}
