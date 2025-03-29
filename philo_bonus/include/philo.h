/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 13:14:34 by samatsum         #+#    #+#             */
/*   Updated: 2025/01/14 18:25:58 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <stdint.h>
# include <stdbool.h>

# define SUCCESS 0
# define INPUT_OK 0
# define FAIL 1
# define PHILO_DEATH 1

# define ALL_OK 0
# define WRONG_INPUT 1
# define MALLOC_ERROR 2

enum e_status
{
	EATING = 0,
	SLEEPING = 1,
	THINKING = 2,
	DEAD = 3,
	IDLE = 4
};

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	int				id;
	int				nb_meals_ate;
	int				usleep_time;
	t_data			*data;
	enum e_status	status;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	pthread_mutex_t	mutex_last_eat_time;
	size_t			last_eat_time;
}t_philo;

typedef struct s_data
{
	int				nb_philos;
	int				nb_must_meals;
	int				nb_odd_philos;
	int				eat_interval_time;
	bool			keep_iterating_flag;
	size_t			eat_time;
	size_t			die_time;
	size_t			sleep_time;
	size_t			simulation_start_time;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_keep_iter;
	pthread_t		monitor_all_alive;
	pthread_t		monitor_all_full;
	pthread_t		*philo_ths;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}t_data;

// check_input.c
int			check_input(int argc, char **argv);
// ft_atoi.c
int			ft_atoi(char *str);
// ft_eat.c
int			ft_eat(t_philo *philo);
// init_data.c
int			init_data(t_data *data, int argc, char **argv);
int			init_philos(t_data *data);
int			init_forks(t_data *data);
// monitor.c
void		*all_full_monitor_routine(void *data_p);
void		*all_alive_monitor_routine(void *data_p);
bool		time_over(t_philo *philo);
// philo_main.c
int			main(int argc, char **argv);
// routine.c
void		*routine(void *philo_p);
void		*special_routine(void *philo_p);
// threads.c
int			run_threads(t_data *data);
int			join_threads(t_data *data);
// utils_02.c
size_t		get_time(void);
void		ft_usleep(size_t time);
void		print_death_msg(t_data *data, int id);
// utils.c
void		free_data(t_data *data);
void		print_msg(t_data *data, int id, char *msg);
bool		get_keep_iterating_flag(t_data *data);
void		set_keep_iterating_flag(t_data *data, bool set_to);
void		set_philo_status(t_philo *philo, enum e_status status);

#endif