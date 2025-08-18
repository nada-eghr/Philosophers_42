/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:23:42 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/18 11:45:13 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
// #include <pthread/sched.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
#include<string.h>
#include <ctype.h>
# include <stdio.h>

typedef struct s_timeval {
    time_t      tv_sec;   // seconds
    suseconds_t tv_usec;  // microseconds (millionths of a second)
} t_timeval;


typedef struct s_data	t_data;

typedef struct s_philo
{
    int         philo_id;
    int         left_fork;
    int         right_fork;
    int         meal_eaten;
    long long   last_meal_eating;
    pthread_t   thread;
    t_data      *data;
} t_philo;       

typedef struct s_data
{
    t_philo         *philo;        
    pthread_mutex_t *forks;
    int             nb_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             nb_time_must_eat;
    int             start_time;
    int             simulation_end; 

} t_data;

long long current_time_ms(void);
void init_philosopher(t_philo *philo , t_data *data);
int init_data(t_data *data , int ac , char **av);
void *routine(void *arg);
void create_philo(t_philo *philo , t_data *data);
void *detect_death(void *arg);
// int is_positive_number(char *str);
// int check_args(char **args);
#endif 