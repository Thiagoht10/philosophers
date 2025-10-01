/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 05:30:08 by thde-sou          #+#    #+#             */
/*   Updated: 2025/10/01 15:54:13 by thde-sou         ###   ########.fr       */
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

    time_now = elapsed_since(philo->app->time_start);
    if(check_stop(philo->app))
        return ;
    pthread_mutex_lock(&philo->app->m_print);
    printf("[%ld] %d %s\n", time_now, philo->id, msg);
    pthread_mutex_unlock(&philo->app->m_print);
}

void    wait_routine(t_philo *philo)
{
    int i;

    i = 0;
    while(i < philo->app->num_philo)
    {
        pthread_join(philo[i].thread, NULL);
        i++;
    }
    pthread_join(philo->app->thread_die, NULL);
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
