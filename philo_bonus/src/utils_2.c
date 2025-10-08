/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 22:14:26 by thde-sou          #+#    #+#             */
/*   Updated: 2025/10/08 01:45:19 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void    error_thread(t_philo *ph)
{
    sem_wait(ph->data->print);
    printf("Error\nMonitor failed\n");
    sem_post(ph->data->print);
    exit(1);
}

long    elapsed_since(long last_time)
{
    long    result;

    result = now_ms() - last_time;
    return (result);
}

void    print_state(t_philo *ph, char *msg)
{
    long    elapsed;

    if(check_died(ph))
        return;
    sem_wait(ph->data->print);
    elapsed = elapsed_since(ph->app->time_start);
    printf("%ld %d %s\n", elapsed, ph->id, msg);
    sem_post(ph->data->print);
}

void    one_philo(t_philo *ph)
{
    if(ph->app->num_philo == 1)
    {
        print_state(ph, "has a fork");
        usleep((ph->app->time_die + 10) * 1000);
        sem_post(ph->data->forks);
        return ;
    }
}
