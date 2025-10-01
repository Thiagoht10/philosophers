/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:06:58 by thde-sou          #+#    #+#             */
/*   Updated: 2025/10/01 15:59:32 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int     all_satisfied(t_philo *ph, t_app *app)
{
    int count;
    int i;

    i = 0;
    count = 0;
    pthread_mutex_lock(&app->m_satisfied);
    while(i < app->num_philo)
    {
        if(ph[i].satisfied)
            count++;
        i++;
    }
    pthread_mutex_unlock(&app->m_satisfied);
    if(count == app->num_philo)
    {
        pthread_mutex_lock(&app->m_stop);
        app->stop = TRUE;
        pthread_mutex_unlock(&app->m_stop);
        return (TRUE);
    }
    return (FALSE);
}

int     check_last_meal(t_philo *ph)
{
    long    check_time;

    pthread_mutex_lock(&ph->app->m_meal);
    check_time = elapsed_since(ph->last_meal);
    pthread_mutex_unlock(&ph->app->m_meal);
    if(check_time >= ph->app->time_die)
        return (FALSE);
    return (TRUE);
}

void    kill(t_philo *ph)
{
    long time_now;

    pthread_mutex_lock(&ph->app->m_stop);
    ph->app->stop = TRUE;
    pthread_mutex_unlock(&ph->app->m_stop);
    usleep(1000);
    pthread_mutex_lock(&ph->app->m_print);
    time_now = elapsed_since(ph->app->time_start);
    printf("[%ld] %d %s\n", time_now, ph->id, "Died");
    pthread_mutex_unlock(&ph->app->m_print);
}

void    *die(void *arg)
{
    t_philo *ph;
    int     i;
    
    ph = (t_philo *)arg;
    while (!check_stop(ph->app))
    {
        i = 0;
        usleep(500);
        if(all_satisfied(ph, ph->app))
        {
            break;
        }
        while (i < ph->app->num_philo)
        {
            if(!check_last_meal(&ph[i]))
            {
                kill(&ph[i]);
                break;
            }
            i++;
        }
    }
    usleep(200);
    return (NULL);
}