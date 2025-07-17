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

int is_positive_number(const char *str)
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
int main (int ac , char **av)
{
    int i = 1; 
    t_arg arg;
    if (ac != 6 )
    {
        printf("wrong number of argumments. \n");
        return 1;
    }
    while ( i < ac)
    {
        if (!is_positive_number(av[i]))
        {
            printf("argument %d is not valid number\n" , i);
            return 0;
        }
        i++;
    }
    arg.num_philos = atoi(av[1]);
    arg.time_to_die = atoi(av[2]);
    arg.time_to_eat = atoi(av[3]);
    arg.time_to_sleep = atoi(av[4]);
    arg.num_time_must_eat = atoi(av[5]);
    
    
    
}