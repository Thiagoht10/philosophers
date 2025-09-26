/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:21:05 by thde-sou          #+#    #+#             */
/*   Updated: 2025/09/26 21:18:23 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void    start_threads(t_philo *ph)
{
    int i;

    i = 0;
    while (i < ph->app->num_philo)
    {
        pthread_create(&ph[i].thread, NULL, routine, &ph[i]);
        pthread_create(&ph[i].thread_die, NULL, die, &ph[i]);
        i++;
    }
}

void    *routine(void *arg)
{
    t_philo *p;
    
    p = (t_philo *)arg;
    while (!p->app->stop && !p->satisfied)
    {
        think(p);
        eat(p);
        sleep_philo(p);
    }
    return (NULL);
}

void    think(t_philo *philo)
{
    long    time_left;
    long    time_think;

    if(philo->app->stop)
        return ;
    pthread_mutex_lock(&philo->app->m_meal);
    time_left = philo->app->time_die - elapsed_since(philo->last_meal);
    pthread_mutex_unlock(&philo->app->m_meal);
    if (time_left <= philo->app->time_eat)
        return ;
    time_think = philo->app->time_die - (philo->app->time_eat * 2) - philo->app->time_sleep;
    if(time_think > 0)
    {
        print_state(philo, "is thinking");
        precise_sleep(philo->app, time_think);
    }
}

void    eat(t_philo *philo)
{
    if(philo->app->stop)
        return ;
    if(philo->meals == 0 && philo->id % 2 == 0)
        usleep((philo->app->time_eat / 2) * 1000);
    get_fork(philo);
    print_state(philo, "is eating");
    pthread_mutex_lock(&philo->app->m_meal);
    philo->last_meal = now_ms();
    philo->meals += 1;
    pthread_mutex_unlock(&philo->app->m_meal);
    usleep(philo->app->time_eat * 1000L);
    drop_fork(philo);
    if(philo->meals == philo->app->num_meals)
        philo->satisfied = 1;
}

void    sleep_philo(t_philo *philo)
{
    if(philo->app->stop)
        return ;
    print_state(philo, "is_sleeping");
    precise_sleep(philo->app, philo->app->time_sleep);
}

