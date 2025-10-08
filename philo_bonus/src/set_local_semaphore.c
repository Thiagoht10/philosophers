/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_local_semaphore.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:35:21 by thde-sou          #+#    #+#             */
/*   Updated: 2025/10/07 18:22:42 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void    create_sem_meal(t_data *data, t_app *app)
{
    data->s_meal = malloc(sizeof(*data->s_meal) * app->num_philo);
    if(!data->s_meal)
    {
        printf("Error\nFailed malloc for semaphore\n");
        free(data->pid);
        exit(EXIT_FAILURE);
    }
}

void    create_sem_died(t_data *data, t_app *app)
{
    data->s_died = malloc(sizeof(*data->s_died) * app->num_philo);
    if(!data->s_died)
    {
        printf("Error\nFailed malloc for semaphore\n");
        free(data->pid);
        exit(EXIT_FAILURE);
    }
}

void    create_sem_satisfied(t_data *data, t_app *app)
{
    data->s_satisfied = malloc(sizeof(*data->s_satisfied) * app->num_philo);
    if(!data->s_satisfied)
    {
        printf("Error\nFailed malloc for semaphore\n");
        free(data->pid);
        exit(EXIT_FAILURE);
    }
}