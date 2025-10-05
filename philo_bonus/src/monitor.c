/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 22:25:00 by thde-sou          #+#    #+#             */
/*   Updated: 2025/10/05 03:16:17 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void    *monitor(void *arg)
{
    t_philo *ph;
    long    last_meal;
    long    elapsed_start;

    ph = (t_philo *)arg;
    while(!ph->died && !ph->satisfied)
    {
        last_meal = elapsed_since(ph->last_meal);
        if(last_meal >= ph->app->time_die)
        {
            ph->died = TRUE;
            sem_wait(ph->data->print);
            elapsed_start = elapsed_since(ph->app->time_start);
            printf("[%ld] %d %s\n", elapsed_start, ph->id, "Died");
            exit(1);
        }
        if(ph->satisfied)
            return (NULL);
        usleep(1000);
    }
    return (NULL);
}

void    ph_exit(t_philo *ph)
{
    if(ph->died)
        exit(1);
    else
        exit(0);
}
