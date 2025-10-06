/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 18:47:57 by thde-sou          #+#    #+#             */
/*   Updated: 2025/10/05 17:24:32 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int    start_philo(t_philo *ph, t_data *data)
{
    int i;
    int id;
    pid_t pid;

    i = 0;
    id = 0;
    while(i < ph->app->num_philo)
    {
        id = i + 1;
        pid = safe_fork();
        if(i == 0)
            ph->app->time_start = now_ms();
        if(pid < 0)
        {
            distroy_pid(i, data);
            return (FALSE);
        }
        else if(pid == 0)
            routine(ph, id);
        else
            (*data).pid[i] = pid;
        i++;
    }
    return (TRUE);
}

void    routine(t_philo *ph, int id)
{
    pthread_t thread;

    ph->id = id;
    ph->last_meal = ph->app->time_start;
    free(ph->data->pid);
    if(pthread_create(&thread, NULL, monitor, ph) != 0)
        error_thread(ph);
    while(!ph->died && !ph->satisfied)
    {
        ph_eat(ph);
        ph_sleep(ph);
        ph_think(ph);
    }
    pthread_join(thread, NULL);
    ph_exit(ph);
}

void    ph_eat(t_philo *ph)
{
    if(ph->died || ph->satisfied)
        return;
    sem_wait(ph->data->forks);
    print_state(ph, "has a fork");
    if(ph->app->num_philo == 1)
    {
        usleep((ph->app->time_die + 10) * 1000);
        sem_post(ph->data->forks);
        return ;
    }
    sem_wait(ph->data->forks);
    print_state(ph, "has a fork");
    ph->last_meal = now_ms();
    ph->meals += 1;
    print_state(ph, "is eating");
    usleep(ph->app->time_eat * 1000);
    sem_post(ph->data->forks);
    sem_post(ph->data->forks);
    if(ph->meals == ph->app->num_meals && ph->app->num_meals != -1)
        ph->satisfied = TRUE;
}

void    ph_sleep(t_philo *ph)
{
    if(ph->died || ph->satisfied)
        return;
    print_state(ph, "is sleeping");
    usleep(ph->app->time_sleep * 1000);
}

void    ph_think(t_philo *ph)
{
    long    time_think;
    long    time_util;

    if(ph->died || ph->satisfied)
        return;
    time_util = ph->app->time_eat + ph->app->time_sleep;
    time_think = (ph->app->time_die - time_util) / 2;
    if(time_think < 1)
        time_think = 1;
    print_state(ph, "is thinking");
    usleep(time_think * 1000);
}
