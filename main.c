/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:22:58 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/17 19:28:40 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_positive_number(char *str)
{
    int i = 0;
    if (!str[0])
        return 0;
    while (str[i])
    {
        if (!isdigit(str[i]))
            return 0;
        i++;
    }
    return 1;
}
int check_args(char **args)
{
    int i = 0;
    while (args[i])
    {
        if (!is_positive_number(args[i]))
            return 0;
        i++;
    }
    return 1;
}
int main (int ac , char **av)
{
    t_data *data;
   
    if (ac < 5 || ac > 6 )
    {
        printf("wrong number of argumments. \n");
        return 1;
    }
    if (!check_args(av+1))
    {
        printf("Invalid arguments: only positive numbers allowed.\n");
        return 1;
    }
    data = malloc(sizeof(t_data));
    if (!data)
        return (1);
    if (init_data(data, ac, av))
    {
        free(data->forks);
        free(data->philo);
        free(data);
        return 1;
    }
   data->simulation_end = 0; 

    create_philo(data->philo, data); 

    detect_death(data); 

    // for (int i = 0; i < data->nb_philos; i++)
    //     pthread_mutex_destroy(&data->forks[i]);


    
    
    
    // free(data->forks);
    // free(data->philo);
    // free(data);
    // return 0;
    
}
