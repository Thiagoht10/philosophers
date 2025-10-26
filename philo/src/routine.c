/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:21:05 by thde-sou          #+#    #+#             */
/*   Updated: 2025/10/26 20:34:45 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	start_threads(t_philo *ph)
{
	int	i;

	i = 0;
	ph->app->time_start = now_ms();
	if (ph->app->time_die == 0)
	{
		print_state(ph, "died");
		return (1);
	}
	while (i < ph->app->num_philo)
	{
		if (pthread_create(&ph[i].thread, NULL, routine, &ph[i]) != 0)
		{
			error_thread(ph, ph->app, i);
			return (FALSE);
		}
		i++;
	}
	if (pthread_create(&ph->app->thread_die, NULL, die, ph) != 0)
	{
		error_thread(ph, ph->app, i);
		return (FALSE);
	}
	return (TRUE);
}

void	*routine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (!check_stop(ph->app))
	{
		eat(ph);
		if (ph->not_meal)
		{
			if (ph->app->num_philo == 1)
				break ;
			else
				continue ;
		}
		sleep_philo(ph);
		think(ph);
	}
	return (NULL);
}

void	think(t_philo *ph)
{
	long	time_think;
	long	time_util;

	time_util = ph->app->time_eat + ph->app->time_sleep;
	time_think = (ph->app->time_die - time_util) / 2;
	if (time_think < 0)
		time_think = 0;
	print_state(ph, "is thinking");
	usleep(time_think * 1000);
}

void	eat(t_philo *ph)
{
	if (ph->meals == 0 && ph->id % 2 == 0)
		usleep((ph->app->time_eat * 1000) / 2);
	get_fork(ph);
	if (ph->num_forks != 2)
	{
		drop_fork(ph);
		ph->not_meal = 1;
		return ;
	}
	ph->not_meal = 0;
	pthread_mutex_lock(&ph->m_meal);
	ph->last_meal = now_ms();
	pthread_mutex_unlock(&ph->m_meal);
	ph->meals += 1;
	print_state(ph, "is eating");
	set_satisfied(ph);
	usleep(ph->app->time_eat * 1000);
	drop_fork(ph);
}

void	sleep_philo(t_philo *ph)
{
	print_state(ph, "is sleeping");
	usleep(ph->app->time_sleep * 1000);
}
