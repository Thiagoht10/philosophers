/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_semaphore.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 22:31:03 by thde-sou          #+#    #+#             */
/*   Updated: 2025/10/08 00:13:45 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	init_sem_meal(t_data *data, int id)
{
	char	name[32];
	char	c_id[4];

	ft_itoa(id, c_id);
	strjoin("/meal", c_id, name);
	sem_unlink(name);
	data->s_meal[id - 1] = sem_open(name, O_CREAT, 0644, 1);
}

void	init_sem_died(t_data *data, int id)
{
	char	name[32];
	char	c_id[4];

	ft_itoa(id, c_id);
	strjoin("/died", c_id, name);
	sem_unlink(name);
	data->s_died[id - 1] = sem_open(name, O_CREAT, 0644, 1);
}

void	init_sem_satisfied(t_data *data, int id)
{
	char	name[32];
	char	c_id[4];

	ft_itoa(id, c_id);
	strjoin("/satisfied", c_id, name);
	sem_unlink(name);
	data->s_satisfied[id - 1] = sem_open(name, O_CREAT, 0644, 1);
}

void	init_local_semaphore(t_data *data, t_philo *ph)
{
	int	i;
	int	id;

	i = 0;
	while (i < ph->app->num_philo)
	{
		id = i + 1;
		init_sem_meal(data, id);
		init_sem_died(data, id);
		init_sem_satisfied(data, id);
		i++;
	}
}
