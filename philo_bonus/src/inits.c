/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:30:11 by thde-sou          #+#    #+#             */
/*   Updated: 2025/10/07 18:23:21 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	inits_app(t_app *app, int argc, char **argv)
{
	app->num_philo = ft_atoi(argv[1]);
	app->time_die = ft_atoi(argv[2]);
	app->time_eat = ft_atoi(argv[3]);
	app->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		app->num_meals = ft_atoi(argv[5]);
	else
		app->num_meals = -1;
}

void	inits_philo(t_philo *ph, t_app *app, t_data *data)
{
	ph->id = 0;
	ph->died = FALSE;
	ph->satisfied = FALSE;
	ph->meals = 0;
	ph->app = app;
	ph->data = data;
}

void	inits_data(t_data *data, t_app *app)
{
	data->pid = malloc(sizeof(pid_t) * app->num_philo);
	if (!data->pid)
	{
		printf("Error\nAllocation failure in inits\n");
		exit(EXIT_FAILURE);
	}
	sem_unlink("/forks");
	data->forks = sem_open("/forks", O_CREAT, 0644, app->num_philo);
	if (data->forks == SEM_FAILED)
	{
		printf("Error\nFailure to create the semaphore\n");
		free(data->pid);
		exit(EXIT_FAILURE);
	}
	sem_unlink("/print");
	data->print = sem_open("/print", O_CREAT, 0644, 1);
	if (data->print == SEM_FAILED)
	{
		printf("Error\nFailure to create the semaphore\n");
		free(data->pid);
		exit(EXIT_FAILURE);
	}
	create_sem_meal(data, app);
	create_sem_died(data, app);
	create_sem_satisfied(data, app);
}
