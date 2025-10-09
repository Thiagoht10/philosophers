/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_global_semaphore.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 02:19:38 by thde-sou          #+#    #+#             */
/*   Updated: 2025/10/09 18:32:26 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	create_sem_fork(t_data *data, t_app *app)
{
	sem_unlink("/forks");
	data->forks = sem_open("/forks", O_CREAT, 0644, app->num_philo);
	if (data->forks == SEM_FAILED)
	{
		printf("Error\nFailure to create the semaphore\n");
		free(data->pid);
		exit(EXIT_FAILURE);
	}
}

void	creat_sem_print(t_data *data)
{
	sem_unlink("/print");
	data->print = sem_open("/print", O_CREAT, 0644, 1);
	if (data->print == SEM_FAILED)
	{
		printf("Error\nFailure to create the semaphore\n");
		free(data->pid);
		exit(EXIT_FAILURE);
	}
}

void	creat_sem_table(t_data *data, t_app *app)
{
	int	num;

	num = app->num_philo / 2;
	if (app->num_philo == 1)
		num = 1;
	sem_unlink("/table");
	data->table = sem_open("/table", O_CREAT, 0644, num);
	if (data->table == SEM_FAILED)
	{
		printf("Error\nFailure to create the semaphore\n");
		free(data->pid);
		exit(EXIT_FAILURE);
	}
}
