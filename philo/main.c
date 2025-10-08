/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:53:19 by thde-sou          #+#    #+#             */
/*   Updated: 2025/10/07 23:04:17 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_app	app;
	t_philo	*philo;

	if (argc < 5 || argc > 6)
	{
		printf("Error\nWrong number arguments\n");
		return (-1);
	}
	if (!check_inputs(argv))
		return (-1);
	if (!inits_app(&app, argv, argc))
		return (-1);
	if (app.num_meals == 0)
		return (-1);
	if (!inits_philo(&app, &philo))
		return (-1);
	start_threads(philo);
	wait_routine(philo);
	distroy_mutex(&app, philo);
	free(philo);
	return (0);
}
