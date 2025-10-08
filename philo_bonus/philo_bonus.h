/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 15:34:42 by thde-sou          #+#    #+#             */
/*   Updated: 2025/10/08 20:07:27 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0

typedef struct s_data
{
	sem_t		*print;
	sem_t		*forks;
	sem_t		**s_satisfied;
	sem_t		**s_died;
	sem_t		**s_meal;
	pid_t		*pid;
	int			status;
	int			code;
	int			all_satisfied;
}				t_data;

typedef struct s_app
{
	int			num_philo;
	long		time_die;
	long		time_eat;
	long		time_sleep;
	long		time_start;
	int			num_meals;
	pthread_t	thread;
}				t_app;

typedef struct s_philo
{
	int			id;
	int			meals;
	long		last_meal;
	int			satisfied;
	int			died;
	t_app		*app;
	t_data		*data;
}				t_philo;

void			check_arguments(int argc, char **argv);
int				ft_atoi(char *s);
long			now_ms(void);
int			inits_app(t_app *app, int argc, char **argv);
void			inits_philo(t_philo *ph, t_app *app, t_data *data);
void			inits_data(t_data *data, t_app *app);
pid_t			safe_fork(void);
void			distroy_pid(int i, t_data *data);
int				start_philo(t_philo *ph, t_data *data);
void			routine(t_philo *ph, int id);
void			error_thread(t_philo *ph);
void			*monitor(void *arg);
long			elapsed_since(long last_time);
void			print_state(t_philo *ph, char *msg);
void			ph_eat(t_philo *ph);
void			ph_sleep(t_philo *ph);
void			ph_think(t_philo *ph);
void			ph_exit(t_philo *ph);
void			wait_children(t_app app, t_data *data);
int				check_exit(t_data *data, t_app app);
void			kill_process(t_data *data, t_app app);
int				str_len(const char *s);
int				ft_itoa_rec(long num, char *buffer, int i);
void			ft_itoa(long num, char *buffer);
void			strjoin(char *s1, char *s2, char *buffer);
void			create_sem_meal(t_data *data, t_app *app);
void			init_sem_meal(t_data *data, int id);
void			close_global_sem(t_data *data);
void			close_sem_meal(t_data *data, t_philo *ph);
void			create_sem_died(t_data *data, t_app *app);
void			close_sem_died(t_data *data, t_philo *ph);
void			create_sem_died(t_data *data, t_app *app);
void			init_sem_died(t_data *data, int id);
int				check_died(t_philo *ph);
void			create_sem_satisfied(t_data *data, t_app *app);
void			init_sem_satisfied(t_data *data, int id);
void			close_sem_satisfied(t_data *data, t_philo *ph);
int				check_satisfied(t_philo *ph);
void			init_local_semaphore(t_data *data, t_philo *ph);
void			one_philo(t_philo *ph);

#endif
