/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:41:54 by thde-sou          #+#    #+#             */
/*   Updated: 2025/10/08 18:01:14 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	get_fork(t_philo *philo)
{
	if ((philo->id % 2) == 0)
	{
		if (philo->right != -1)
		{
			pthread_mutex_lock(&philo->app->forks[philo->right]);
			print_state(philo, "has taken a fork");
		}
		else
			precise_sleep(philo->app, philo->app->time_die * 2);
		pthread_mutex_lock(&philo->app->forks[philo->left]);
		print_state(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->app->forks[philo->left]);
		print_state(philo, "has taken a fork");
		if (philo->right != -1)
		{
			pthread_mutex_lock(&philo->app->forks[philo->right]);
			print_state(philo, "has taken a fork");
		}
		else
			precise_sleep(philo->app, philo->app->time_die * 2);
	}
}

void	drop_fork(t_philo *ph)
{
	if ((ph->id % 2) == 0)
	{
		if (ph->right != -1)
			pthread_mutex_unlock(&ph->app->forks[ph->right]);
		pthread_mutex_unlock(&ph->app->forks[ph->left]);
	}
	else
	{
		pthread_mutex_unlock(&ph->app->forks[ph->left]);
		if (ph->right != -1)
			pthread_mutex_unlock(&ph->app->forks[ph->right]);
	}
}

void	distroy_mutex(t_app *app, t_philo *ph)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&app->m_print);
	pthread_mutex_destroy(&app->m_stop);
	while (i < app->num_philo)
	{
		pthread_mutex_destroy(&app->forks[i]);
		pthread_mutex_destroy(&(ph)[i].m_meal);
		pthread_mutex_destroy(&(ph)[i].m_satisfied);
		i++;
	}
	free(app->forks);
}

void	precise_sleep(t_app *app, long ms)
{
	long	elapsed;
	long	start;

	start = now_ms();
	while (!check_stop(app))
	{
		elapsed = now_ms() - start;
		if (elapsed >= ms)
		{
			break ;
		}
		usleep(200);
	}
}

int	init_local_mutex(t_philo *ph, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	if (pthread_mutex_init(&(ph)[i].m_meal, NULL) != 0)
	{
		while (j < i)
			pthread_mutex_destroy(&(ph)[j++].m_meal);
		return (FALSE);
	}
	if (pthread_mutex_init(&(ph)[i].m_satisfied, NULL) != 0)
	{
		while (j < ph->app->num_philo)
			pthread_mutex_destroy(&(ph)[j++].m_meal);
		while (k < i)
			pthread_mutex_destroy(&(ph)[k++].m_satisfied);
		return (FALSE);
	}
	return (TRUE);
}
