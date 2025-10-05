/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 15:34:42 by thde-sou          #+#    #+#             */
/*   Updated: 2025/10/05 01:16:57 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>

#define TRUE 1
#define FALSE 0

typedef struct s_data
{
    sem_t *print;
    sem_t *forks;
    pid_t *pid;
    int status;
    int code;
    int all_satisfied;
}           t_data;

typedef struct s_app
{
    int     num_philo;
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
    long    last_meal;
    int satisfied;
    int died;
    t_app   *app;
    t_data  *data;
}           t_philo;

void    check_arguments(int argc, char **argv);
int ft_atoi(char *s);
long    now_ms(void);
void    inits_app(t_app *app, int argc, char **argv);
void    inits_philo(t_philo *ph, t_app *app, t_data *data);
void    inits_data(t_data *data, t_app app);
pid_t safe_fork(void);
void    distroy_pid(int i, t_data *data);
int    start_philo(t_philo *ph, t_data *data);
void    routine(t_philo *ph, int id);
void    error_thread(t_philo *ph);
void    *monitor(void *arg);
long    elapsed_since(long last_time);
void    print_state(t_philo *ph, char *msg);
void    ph_eat(t_philo *ph);
void    ph_sleep(t_philo *ph);
void    ph_think(t_philo *ph);
void    ph_exit(t_philo *ph);
void    wait_children(t_app app, t_data *data);
int check_exit(t_data *data, t_app app);
void kill_process(t_data *data, t_app app);

#endif
