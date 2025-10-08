/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_sem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:38:53 by thde-sou          #+#    #+#             */
/*   Updated: 2025/10/08 00:14:40 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	close_global_sem(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->print);
	sem_unlink("/print");
	sem_unlink("/forks");
}

void	close_sem_meal(t_data *data, t_philo *ph)
{
	int		i;
	int		id;
	char	num[5];
	char	name[32];

	i = 0;
	while (i < ph->app->num_philo)
	{
		id = i + 1;
		ft_itoa(id, num);
		strjoin("/meal", num, name);
		sem_close(data->s_meal[i]);
		sem_unlink(name);
		i++;
	}
	free(data->s_meal);
}

void	close_sem_died(t_data *data, t_philo *ph)
{
	int		i;
	int		id;
	char	num[5];
	char	name[32];

	i = 0;
	while (i < ph->app->num_philo)
	{
		id = i + 1;
		ft_itoa(id, num);
		strjoin("/died", num, name);
		sem_close(data->s_died[i]);
		sem_unlink(name);
		i++;
	}
	free(data->s_died);
}

void	close_sem_satisfied(t_data *data, t_philo *ph)
{
	int		i;
	int		id;
	char	num[5];
	char	name[32];

	i = 0;
	while (i < ph->app->num_philo)
	{
		id = i + 1;
		ft_itoa(id, num);
		strjoin("/satisfied", num, name);
		sem_close(data->s_satisfied[i]);
		sem_unlink(name);
		i++;
	}
	free(data->s_satisfied);
}
