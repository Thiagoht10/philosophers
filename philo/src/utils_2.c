/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:41:54 by thde-sou          #+#    #+#             */
/*   Updated: 2025/09/25 05:46:18 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void    get_fork(t_philo *philo)
{
    if((philo->id % 2) == 0)
    {
        pthread_mutex_lock(&philo->app->forks[philo->right]);
        print_state(philo, "has taken a fork");
        pthread_mutex_lock(&philo->app->forks[philo->left]);
        print_state(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(&philo->app->forks[philo->left]);
        print_state(philo, "has taken a fork");
        pthread_mutex_lock(&philo->app->forks[philo->right]);
        print_state(philo, "has taken a fork");
    }
}

void    drop_fork(t_philo *philo)
{
    if((philo->id % 2) == 0)
    {
        pthread_mutex_unlock(&philo->app->forks[philo->right]);
        pthread_mutex_unlock(&philo->app->forks[philo->left]);
    }
    else
    {
        pthread_mutex_unlock(&philo->app->forks[philo->left]);
        pthread_mutex_unlock(&philo->app->forks[philo->right]);
    }
}

void    distroy_mutex(t_app *app)
{
    int i;

    i = 0;
    pthread_mutex_destroy(&app->m_meal);
    pthread_mutex_destroy(&app->m_print);
    while(i < app->num_philo)
    {
        pthread_mutex_destroy(&app->forks[i]);
        i++;
    }
    free(app->forks);
}
