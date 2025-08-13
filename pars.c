/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:22:58 by naessgui          #+#    #+#             */
/*   Updated: 2025/07/14 16:35:24 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include<ctype.h>

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
   
    t_arg arg;
    if (ac < 5 || ac > 6 )
    {
        printf("wrong number of argumments. \n");
        return 1;
    }
    if (!check_args(av + 1))
    {
        printf("arguments are not valid number\n");
    }
    arg.num_philos = atoi(av[1]);
    arg.time_to_die = atoi(av[2]);
    arg.time_to_eat = atoi(av[3]);
    arg.time_to_sleep = atoi(av[4]);
    arg.num_time_must_eat = atoi(av[5]);
    
    
    
}