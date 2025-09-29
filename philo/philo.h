/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:33:57 by thde-sou          #+#    #+#             */
/*   Updated: 2025/09/28 02:49:10 by thde-sou         ###   ########.fr       */
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
    pthread_t   serve;
    pthread_mutex_t *forks;
    pthread_mutex_t m_print;
    pthread_mutex_t m_meal;
    pthread_mutex_t m_stop;
    pthread_mutex_t m_satisfied;
    long    time_die;
    long    time_eat;
    long    time_sleep;
    long    time_start;
    int     num_meals;
    int     stop;
}           t_app;

typedef struct s_philo
{
    int id;
    int meals;
    long last_meal;
    int satisfied;
    int right;
    int left;
    pthread_t   thread;
    pthread_t   thread_die;
    t_app   *app;
}           t_philo;

int check_inputs(char **argv);
int    inits_app(t_app *app, char **argv, int argc);
int    inits_philo(t_app *app, t_philo **philos);
void *routine(void *arg);
void    start_threads(t_philo *philos);
long    now_ms(void);
int inits_fork(t_app *app);
long    elapsed_since(long last_time);
void    think(t_philo *philo);
void    print_state(t_philo *philo, char *msg);
void    wait_routine(t_philo *philo);
void    eat(t_philo *philo);
void    *die(void *arg);
int    init_mutex(t_app *app);
void    get_fork(t_philo *philo);
void    drop_fork(t_philo *philo);
void    sleep_philo(t_philo *philo);
void    distroy_mutex(t_app *app);
void precise_sleep(t_app *app, long ms);
int     check_stop(t_app *app);
int     check_satisfied(t_philo *ph);
void    set_satisfied(t_philo *ph);
long    calcule_think(t_philo *ph);
#endif
