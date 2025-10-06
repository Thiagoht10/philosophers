/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_semaphore.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 22:31:03 by thde-sou          #+#    #+#             */
/*   Updated: 2025/10/06 22:54:04 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void    init_sem_meal(t_data *data, t_philo *ph, int id)
{
    int i;
    char *name;
    char    c_id[4];

    data->s_meal = malloc(sizeof(*data->s_meal) * ph->app->num_philo);
    if(!data->s_meal)
    {
        printf("Error\nFailed malloc for semaphore\n");
        exit(EXIT_FAILURE);
    }
    i = 0;
    while(i < ph->app->num_philo)
    {
        ft_itoa(id, c_id);
        name = strjoin("/meal", c_id);
        sem_unlink(name);
        data->s_meal[i] = sem_open(name, O_CREAT, 0644, 1);
    }
}
