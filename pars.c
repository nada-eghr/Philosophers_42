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
   
    
    
    
}