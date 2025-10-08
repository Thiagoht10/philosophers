/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 05:30:08 by thde-sou          #+#    #+#             */
/*   Updated: 2025/10/07 22:18:41 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(char *s)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (s[i] == 32 || s[i] == 9)
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign *= -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + (s[i] - '0');
		i++;
	}
	return (result * sign);
}

long	elapsed_since(long last_time)
{
	long	result;

	result = now_ms() - last_time;
	return (result);
}

void	print_state(t_philo *ph, char *msg)
{
	long	time_now;

	if (check_stop(ph->app))
		return ;
	pthread_mutex_lock(&ph->app->m_print);
	time_now = elapsed_since(ph->app->time_start);
	printf("%ld %d %s\n", time_now, ph->id, msg);
	pthread_mutex_unlock(&ph->app->m_print);
}

void	wait_routine(t_philo *ph)
{
	int	i;

	i = 0;
	while (i < ph->app->num_philo)
	{
		pthread_join(ph[i].thread, NULL);
		i++;
	}
	pthread_join(ph->app->thread_die, NULL);
}

int	init_mutex(t_app *app)
{
	if (pthread_mutex_init(&app->m_print, NULL) != 0)
		return (FALSE);
	if (pthread_mutex_init(&app->m_stop, NULL) != 0)
	{
		pthread_mutex_destroy(&app->m_print);
		return (FALSE);
	}
	return (TRUE);
}
