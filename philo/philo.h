/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:33:57 by thde-sou          #+#    #+#             */
/*   Updated: 2025/10/07 23:23:39 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0

typedef struct s_app
{
	int				num_philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_stop;
	pthread_t		thread_die;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			time_start;
	int				num_meals;
	int				stop;
}					t_app;

typedef struct s_philo
{
	int				id;
	int				meals;
	long			last_meal;
	int				satisfied;
	int				right;
	int				left;
	pthread_t		thread;
	pthread_mutex_t	m_satisfied;
	pthread_mutex_t	m_meal;
	t_app			*app;
}					t_philo;

int					check_inputs(char **argv);
int					inits_app(t_app *app, char **argv, int argc);
int					inits_philo(t_app *app, t_philo **philo);
void				*routine(void *arg);
void				start_threads(t_philo *ph);
long				now_ms(void);
int					inits_fork(t_app *app);
long				elapsed_since(long last_time);
void				think(t_philo *ph);
void				print_state(t_philo *ph, char *msg);
void				wait_routine(t_philo *ph);
void				eat(t_philo *philo);
void				*die(void *arg);
int					init_mutex(t_app *app);
void				get_fork(t_philo *ph);
void				drop_fork(t_philo *ph);
void				sleep_philo(t_philo *ph);
void	distroy_mutex(t_app *app, t_philo *ph);
void				precise_sleep(t_app *app, long ms);
int					check_stop(t_app *app);
int	check_satisfied(t_philo *ph);
void	set_satisfied(t_philo *ph);
int	check_last_meal(t_philo *ph, int i);
void				kill(t_philo *ph);
int					all_satisfied(t_philo *ph, t_app *app);
int 				ft_atoi(char *s);
int	init_local_mutex(t_philo *ph, int i);
int	alloc_philo(t_app *app, t_philo **ph);
#endif
