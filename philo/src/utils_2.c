/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:41:54 by thde-sou          #+#    #+#             */
/*   Updated: 2025/09/26 19:51:40 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void    get_fork(t_philo *philo)
{
    if((philo->id % 2) == 0)
    {
        if(philo->right != -1)
        {
            pthread_mutex_lock(&philo->app->forks[philo->right]);
            print_state(philo, "has taken a fork");
        }
        else
            precise_sleep(philo->app, philo->app->time_die);
        pthread_mutex_lock(&philo->app->forks[philo->left]);
        print_state(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(&philo->app->forks[philo->left]);
        print_state(philo, "has taken a fork");
        if(philo->right != -1)
        {
            pthread_mutex_lock(&philo->app->forks[philo->right]);
            print_state(philo, "has taken a fork");
        }
        else
            precise_sleep(philo->app, philo->app->time_die);
    }
}

void    drop_fork(t_philo *philo)
{
    if((philo->id % 2) == 0)
    {
        if(philo->right != -1)
            pthread_mutex_unlock(&philo->app->forks[philo->right]);
        pthread_mutex_unlock(&philo->app->forks[philo->left]);
    }
    else
    {
        pthread_mutex_unlock(&philo->app->forks[philo->left]);
        if(philo->right != -1)
            pthread_mutex_unlock(&philo->app->forks[philo->right]);
    }
}

void    distroy_mutex(t_app *app)
{
    int i;

    i = 0;
    pthread_mutex_destroy(&app->m_meal);
    pthread_mutex_destroy(&app->m_print);
    pthread_mutex_destroy(&app->m_stop);
    while(i < app->num_philo)
    {
        pthread_mutex_destroy(&app->forks[i]);
        i++;
    }
    free(app->forks);
}

int check_hungre(t_philo **philo)
{
    int i;

    i = 0;
    while(i < (*philo)[0].app->num_philo)
    {
        if((*philo)[i].satisfied != 1)
            return (FALSE);
        i++;
    }
    pthread_mutex_lock(&(*philo)->app->m_stop);
    (*philo)[0].app->stop = 1;
    pthread_mutex_unlock(&(*philo)->app->m_stop);
    return (TRUE);
}

void precise_sleep(t_app *app, long ms)
{
    long elapsed;
    long start;
    
    start = now_ms();
    while (!app->stop)
    {
        elapsed = now_ms() - start;
        if (elapsed >= ms)
        {
            break;
        }
        usleep(200);
    }
}
