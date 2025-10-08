/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:06:00 by thde-sou          #+#    #+#             */
/*   Updated: 2025/10/07 23:25:08 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_inputs(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Error\nWrong input\n");
				return (FALSE);
			}
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	inits_app(t_app *app, char **argv, int argc)
{
	app->num_philo = ft_atoi(argv[1]);
	if (app->num_philo < 1)
	{
		printf("Error\nWrong number of philosophers\n");
		return (FALSE);
	}
	app->time_die = ft_atoi(argv[2]);
	app->time_eat = ft_atoi(argv[3]);
	app->time_sleep = ft_atoi(argv[4]);
	app->num_meals = -1;
	app->stop = 0;
	if (argc == 6)
		app->num_meals = ft_atoi(argv[5]);
	app->time_start = now_ms();
	app->forks = malloc(sizeof(pthread_mutex_t) * app->num_philo);
	if (!app->forks)
	{
		printf("Error\nFailed to allocate forks\n");
		return (FALSE);
	}
	if (!inits_fork(app))
		return (FALSE);
	if (!init_mutex(app))
		return (FALSE);
	return (TRUE);
}

int	inits_philo(t_app *app, t_philo **philo)
{
	int	i;

	if (!alloc_philo(app, philo))
		return (FALSE);
	i = 0;
	while (i < app->num_philo)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].app = app;
		(*philo)[i].last_meal = app->time_start;
		(*philo)[i].meals = 0;
		(*philo)[i].satisfied = 0;
		(*philo)[i].left = i;
		if (app->num_philo >= 2)
			(*philo)[i].right = (i + 1) % app->num_philo;
		else
			(*philo)[i].right = -1;
		if (!init_local_mutex(*philo, i))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

long	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

int	inits_fork(t_app *app)
{
	int	i;

	i = 0;
	while (i < app->num_philo)
	{
		if (pthread_mutex_init(&app->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&app->forks[i]);
			free(app->forks);
			app->forks = NULL;
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
