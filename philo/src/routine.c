/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:21:05 by thde-sou          #+#    #+#             */
/*   Updated: 2025/10/07 23:10:39 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	start_threads(t_philo *ph)
{
	int	i;

	i = 0;
	ph->app->time_start = now_ms();
	if (ph->app->time_die == 0)
	{
		print_state(ph, "Died");
		return ;
	}
	while (i < ph->app->num_philo)
	{
		pthread_create(&ph[i].thread, NULL, routine, &ph[i]);
		i++;
	}
	pthread_create(&ph[0].app->thread_die, NULL, die, ph);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (!check_stop(p->app))
	{
		eat(p);
		sleep_philo(p);
		think(p);
	}
	return (NULL);
}

void	think(t_philo *ph)
{
	long	time_think;
	long	time_util;

	if (check_satisfied(ph))
		return ;
	time_util = ph->app->time_eat + ph->app->time_sleep;
	time_think = (ph->app->time_die - time_util) / 2;
	if (time_think < 0)
		time_think = 0;
	print_state(ph, "is thinking");
	usleep(time_think * 1000);
}

void	eat(t_philo *ph)
{
	if (check_satisfied(ph))
		return ;
	if (ph->meals == 0 && ph->id % 2 == 0)
		usleep((ph->app->time_eat * 1000) / 2);
	get_fork(ph);
	pthread_mutex_lock(&ph->m_meal);
	if (ph->right != -1)
		ph->last_meal = now_ms();
	pthread_mutex_unlock(&ph->m_meal);
	if (ph->right != -1)
	{
		print_state(ph, "is eating");
		ph->meals += 1;
	}
	usleep(ph->app->time_eat * 1000);
	drop_fork(ph);
	set_satisfied(ph);
}

void	sleep_philo(t_philo *ph)
{
	if (check_satisfied(ph))
		return ;
	print_state(ph, "is sleeping");
	usleep(ph->app->time_sleep * 1000);
}
