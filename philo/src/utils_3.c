/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:46:33 by thde-sou          #+#    #+#             */
/*   Updated: 2025/10/02 12:43:04 by thde-sou         ###   ########.fr       */
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

	pthread_mutex_lock(&ph->app->m_satisfied);
	result = ph->satisfied;
	pthread_mutex_unlock(&ph->app->m_satisfied);
	return (result);
}

void	set_satisfied(t_philo *ph)
{
	pthread_mutex_lock(&ph->app->m_satisfied);
	if (ph->meals == ph->app->num_meals)
		ph->satisfied = 1;
	pthread_mutex_unlock(&ph->app->m_satisfied);
}
