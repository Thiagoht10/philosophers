/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:12:42 by thde-sou          #+#    #+#             */
/*   Updated: 2025/10/09 01:57:07 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_app	app;
	t_philo	ph;
	t_data	data;

	check_arguments(argc, argv);
	if (!inits_app(&app, argc, argv))
		return (-1);
	inits_data(&data, &app);
	inits_philo(&ph, &app, &data);
	if (app.num_meals == 0)
		return (0);
	if (!start_philo(&ph, &data))
	{
		free(data.pid);
		exit(EXIT_FAILURE);
	}
	wait_children(app, &data);
	close_global_sem(&data);
	close_sem_meal(&data, &ph);
	close_sem_died(&data, &ph);
	close_sem_satisfied(&data, &ph);
	free(data.pid);
	return (0);
}
