/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:21:05 by thde-sou          #+#    #+#             */
/*   Updated: 2025/09/24 20:53:26 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void    start_threads(t_philo *philo)
{
    int i;

    i = 0;
    while(i < philo->app->num_philo)
    {
        pthread_create(&philo[i].thread, NULL, routine, &philo[i]);
        pthread_create(&philo[i].thread_die, NULL, die, &philo[i]);
        i++;
    }
}

void    *routine(void *arg)
{
    t_philo *p;
    
    p = (t_philo *)arg;

    while (!p->app->stop)
    {
        think(p);
        if (p->meals < p->app->num_meals)
            eat(p);
        if (p->meals == p->app->num_meals)
            return (NULL);
    }
    return (NULL);
}

void    think(t_philo *philo)
{
    long    time_left;
    long    time_think;

    time_left = philo->app->time_die - elapsed_since(philo->last_meal);
    if (time_left <= philo->app->time_eat)
        return ;
    print_state(philo, "is thinking");
    time_think = time_left - (philo->app->time_eat + philo->app->time_eat);
    if(time_think > 0)
        usleep(time_think * 1000L);
}

void    eat(t_philo *philo)
{
    get_fork(philo);
    print_state(philo, "is eating");
    pthread_mutex_lock(&philo->app->m_meal);
    philo->last_meal = now_ms();
    pthread_mutex_unlock(&philo->app->m_meal);
    usleep(philo->app->time_eat * 1000L);
    philo->meals += 1;
    drop_fork(philo);
}

