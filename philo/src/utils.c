/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 05:30:08 by thde-sou          #+#    #+#             */
/*   Updated: 2025/09/27 21:51:24 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long    elapsed_since(long last_time)
{
    long    result;

    result = now_ms() - last_time;
    return (result);
}

void    print_state(t_philo *philo, char *msg)
{
    long time_now;

    if (!check_stop(philo->app))
    {
        pthread_mutex_lock(&philo->app->m_print);
        time_now = elapsed_since(philo->app->time_start);
        printf("[%ld] %d %s\n", time_now, philo->id, msg);
        pthread_mutex_unlock(&philo->app->m_print);
    }
}

void    wait_routine(t_philo *philo)
{
    int i;

    i = 0;
    while(i < philo->app->num_philo)
    {
        pthread_join(philo[i].thread, NULL);
        pthread_join(philo[i].thread_die, NULL);
        i++;
    }
}

int    init_mutex(t_app *app)
{
    if(pthread_mutex_init(&app->m_print, NULL) != 0)
        return (FALSE);
    if(pthread_mutex_init(&app->m_meal, NULL) != 0)
    {
        pthread_mutex_destroy(&app->m_print);
        return (FALSE);
    }
    if(pthread_mutex_init(&app->m_stop, NULL) != 0)
    {
        pthread_mutex_destroy(&app->m_print);
        pthread_mutex_destroy(&app->m_meal);
        return (FALSE);
    }
    if(pthread_mutex_init(&app->m_satisfied, NULL) != 0)
    {
        pthread_mutex_destroy(&app->m_print);
        pthread_mutex_destroy(&app->m_meal);
        pthread_mutex_destroy(&app->m_stop);
        return (FALSE);
    }
    return (TRUE);
}

void    *die(void *arg)
{
    t_philo *p;
    long    check_time;
    long    time_now;
    
    p = (t_philo *)arg;
    while (!check_stop(p->app))
    {
        pthread_mutex_lock(&p->app->m_meal);
        check_time = elapsed_since(p->last_meal);
        pthread_mutex_unlock(&p->app->m_meal);
        if(check_time >= p->app->time_die)
        {
            pthread_mutex_lock(&p->app->m_stop);
            if(p->app->stop == 1)
            {
                break;
            }
            p->app->stop = 1;
            pthread_mutex_lock(&p->app->m_print);
            time_now = elapsed_since(p->app->time_start);
            printf("[%ld] %d %s\n", time_now, p->id, "died");
            pthread_mutex_unlock(&p->app->m_print);
            pthread_mutex_unlock(&p->app->m_stop);
        }
        if(check_stop(p->app) || check_satisfied(p))
        {
            break;
        }
    }
    usleep(200);
    return (NULL);
}
