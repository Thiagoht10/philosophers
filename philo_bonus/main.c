/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:12:42 by thde-sou          #+#    #+#             */
/*   Updated: 2025/10/05 17:26:12 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int main(int argc, char **argv)
{
    t_app app;
    t_philo ph;
    t_data data;
    
    check_arguments(argc, argv);
    inits_app(&app, argc, argv);
    inits_data(&data, app);
    inits_philo(&ph, &app, &data);
    if(!start_philo(&ph, &data))
    {
        free(data.pid);
        exit(EXIT_FAILURE);
    }
    wait_children(app, &data);
    sem_close(data.forks);
    sem_close(data.print);
    sem_unlink("/print");
    sem_unlink("/forks");
    free(data.pid);
    return (0);
}
