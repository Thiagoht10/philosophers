/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:21:05 by thde-sou          #+#    #+#             */
/*   Updated: 2025/10/01 15:56:29 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void    start_threads(t_philo *ph)
{
    int i;

    i = 0;
    ph->app->time_start = now_ms();
    while (i < ph->app->num_philo)
    {
        pthread_create(&ph[i].thread, NULL, routine, &ph[i]);
        i++;
    }
    pthread_create(&ph[0].app->thread_die, NULL, die, ph);
}

void    *routine(void *arg)
{
    t_philo *p;
    
    p = (t_philo *)arg;
    while (!check_stop(p->app))
    {
        eat(p);
        sleep_philo(p);
        think(p);
    }
    return (NULL);
}

void    think(t_philo *ph)
{
    long    time_think;
    long    time_util;

    time_util = ph->app->time_eat + ph->app->time_sleep;
    time_think = (ph->app->time_die - time_util) / 2;
    if(time_think < 1)
        time_think = 1;
    print_state(ph, "is thinking");
    usleep(time_think * 1000);
}

void    eat(t_philo *philo)
{
    if(philo->meals == 0 && philo->id % 2 == 0)
        usleep((philo->app->time_eat * 1000) / 2);
    get_fork(philo);
    pthread_mutex_lock(&philo->app->m_meal);
    philo->last_meal = now_ms();
    pthread_mutex_unlock(&philo->app->m_meal);
    print_state(philo, "is eating");
    philo->meals += 1;
    usleep(philo->app->time_eat * 1000);
    drop_fork(philo);
    set_satisfied(philo);
}

void    sleep_philo(t_philo *philo)
{
    print_state(philo, "is sleeping");
    usleep(philo->app->time_sleep * 1000);
}

