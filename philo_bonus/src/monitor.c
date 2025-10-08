/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 22:25:00 by thde-sou          #+#    #+#             */
/*   Updated: 2025/10/08 01:30:22 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void    *monitor(void *arg)
{
    t_philo *ph;
    long    last_meal;
    long    elapsed_start;

    ph = (t_philo *)arg;
    while(!check_died(ph))
    {
        usleep(5000);
        sem_wait(ph->data->s_meal[ph->id - 1]);
        last_meal = elapsed_since(ph->last_meal);
        sem_post(ph->data->s_meal[ph->id - 1]);
        if(last_meal >= ph->app->time_die)
        {
            sem_wait(ph->data->s_died[ph->id - 1]);
            ph->died = TRUE;
            sem_post(ph->data->s_died[ph->id - 1]);
            sem_wait(ph->data->print);
            elapsed_start = elapsed_since(ph->app->time_start);
            printf("%ld %d %s\n", elapsed_start, ph->id, "Died");
            return (NULL);
        }
        if(check_satisfied(ph))
            return (NULL);
    }
    return (NULL);
}

void    ph_exit(t_philo *ph)
{
    if(check_died(ph))
    {
        close_global_sem(ph->data);
        close_sem_meal(ph->data, ph);
        close_sem_satisfied(ph->data, ph);
        close_sem_died(ph->data, ph);
        exit(1);
    }
    else
    {
        close_global_sem(ph->data);
        close_sem_meal(ph->data, ph);
        close_sem_satisfied(ph->data, ph);
        close_sem_died(ph->data, ph);
        exit(0);
    }
}

int    check_died(t_philo *ph)
{
    int died;

    sem_wait(ph->data->s_died[ph->id - 1]);
    died = ph->died;
    sem_post(ph->data->s_died[ph->id - 1]);
    return (died);
}

int check_satisfied(t_philo *ph)
{
    int satisfied;

    sem_wait(ph->data->s_satisfied[ph->id - 1]);
    satisfied = ph->satisfied;
    sem_post(ph->data->s_satisfied[ph->id - 1]);
    return (satisfied);
}
