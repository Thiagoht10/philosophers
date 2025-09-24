/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:53:19 by thde-sou          #+#    #+#             */
/*   Updated: 2025/09/24 17:36:01 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_app app;
    t_philo *philos;

    if(argc < 5 || argc > 6)
    {
        printf("Error\nWrong number arguments\n");
        return (-1);
    }
    if(!check_inputs(argv))
        return (-1);
    if(!inits_app(&app, argv, argc))
        return (-1);
    if(!inits_philo(&app, &philos))
        return (-1);
    start_threads(philos);
    wait_routine(philos);
    return (0);
}
