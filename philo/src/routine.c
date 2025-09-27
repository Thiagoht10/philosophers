/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:21:05 by thde-sou          #+#    #+#             */
/*   Updated: 2025/09/27 21:21:48 by thde-sou         ###   ########.fr       */
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
    while (!check_stop(p->app) && !check_satisfied(p))
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

    if(check_stop(philo->app))
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
    long time_eat;

    if(check_stop(philo->app))
        return ;
    if(philo->meals == 0 && philo->id % 2 == 0)
        usleep((philo->app->time_eat / 2) * 1000);
    get_fork(philo);
    pthread_mutex_lock(&philo->app->m_meal);
    philo->last_meal = now_ms();
    philo->meals += 1;
    time_eat = philo->app->time_eat;
    pthread_mutex_unlock(&philo->app->m_meal);
    print_state(philo, "is eating");
    usleep(time_eat * 1000L);
    drop_fork(philo);
    set_satisfied(philo);
}

void    sleep_philo(t_philo *philo)
{
    if(check_stop(philo->app))
        return ;
    print_state(philo, "is_sleeping");
    precise_sleep(philo->app, philo->app->time_sleep);
}

