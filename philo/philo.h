/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:33:57 by thde-sou          #+#    #+#             */
/*   Updated: 2025/09/23 20:05:08 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define TRUE 1
#define FALSE 0

typedef struct s_app
{
    int num_philo;
    pthread_mutex_t *forks;
    long    time_die;
    long    time_eat;
    long    time_sleep;
    long    time_start;
    int     num_meals;
}           t_app;

typedef struct s_philo
{
    int id;
    int meals;
    long last_meal;
    int right;
    int left;
    pthread_t   thread;
    t_app   *app;
}           t_philo;

int check_inputs(char **argv);
int    inits_app(t_app *app, char **argv, int argc);
int    inits_philo(t_app *app, t_philo **philos);
void *routine(void *arg);
void    start_threads(t_philo *philos);
long    now_ms(void);
int inits_fork(t_app *app);

#endif
