/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:46:33 by thde-sou          #+#    #+#             */
/*   Updated: 2025/10/08 16:48:49 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_stop(t_app *app)
{
	int	result;

	pthread_mutex_lock(&app->m_stop);
	result = app->stop;
	pthread_mutex_unlock(&app->m_stop);
	return (result);
}

int	check_satisfied(t_philo *ph)
{
	int	result;

	pthread_mutex_lock(&ph->m_satisfied);
	result = ph->satisfied;
	pthread_mutex_unlock(&ph->m_satisfied);
	return (result);
}

void	set_satisfied(t_philo *ph)
{
	if (ph->meals == ph->app->num_meals && ph->app->num_meals != -1)
	{
		pthread_mutex_lock(&ph->m_satisfied);
		ph->satisfied = 1;
		pthread_mutex_unlock(&ph->m_satisfied);
	}
}

int	alloc_philo(t_app *app, t_philo **ph)
{
	*ph = malloc(sizeof(t_philo) * app->num_philo);
	if (!*ph)
	{
		printf("Error\nFailed to allocate philosophers\n");
		return (FALSE);
	}
	return (TRUE);
}
