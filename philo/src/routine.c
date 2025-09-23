/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:21:05 by thde-sou          #+#    #+#             */
/*   Updated: 2025/09/23 19:19:10 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void    start_threads(t_philo *philos)
{
    int i;

    i = 0;
    while(i < philos->app->num_philo)
    {
        pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
        i++;
    }
}

void    *routine(void *arg)
{
    t_philo *p = (t_philo *)arg;

    p->meals = 0;
    return (NULL);
}

