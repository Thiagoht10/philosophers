/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:41:54 by thde-sou          #+#    #+#             */
/*   Updated: 2025/09/27 21:41:53 by thde-sou         ###   ########.fr       */
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
            print_state(philo, "has taken a fork - right");
        }
        else
            precise_sleep(philo->app, philo->app->time_die);
        pthread_mutex_lock(&philo->app->forks[philo->left]);
        print_state(philo, "has taken a fork - left");
    }
    else
    {
        pthread_mutex_lock(&philo->app->forks[philo->left]);
        print_state(philo, "has taken a fork - left");
        if(philo->right != -1)
        {
            pthread_mutex_lock(&philo->app->forks[philo->right]);
            print_state(philo, "has taken a fork - right");
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
    pthread_mutex_destroy(&app->m_satisfied);
    while(i < app->num_philo)
    {
        pthread_mutex_destroy(&app->forks[i]);
        i++;
    }
    free(app->forks);
}

void precise_sleep(t_app *app, long ms)
{
    long elapsed;
    long start;
    
    start = now_ms();
    while (!check_stop(app))
    {
        elapsed = now_ms() - start;
        if (elapsed >= ms)
        {
            break;
        }
        usleep(200);
    }
}
