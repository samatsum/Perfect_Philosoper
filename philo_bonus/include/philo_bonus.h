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

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <stdint.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

# define SUCCESS 0
# define INPUT_OK 0
# define FAIL 1
# define PHILO_DEATH 1

# define ALL_OK 0
# define WRONG_INPUT 1
# define MALLOC_ERROR 2

# define SEM_FORKS "/sem_forks"
# define SEM_PRINT "/sem_print"
# define SEM_DEAD "/sem_dead"
# define SEM_MEALS "/sem_meals"
# define SEM_PHILO_DEAD "/sem_philo_dead_"

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
	pid_t			pid;
	t_data			*data;
	enum e_status	status;
	sem_t			*philo_dead_sem;
	char			philo_dead_sem_name[30];
	size_t			last_eat_time;
}t_philo;

typedef struct s_data
{
	int				nb_philos;
	int				nb_must_meals;
	bool			keep_iterating_flag;
	size_t			eat_time;
	size_t			die_time;
	size_t			sleep_time;
	size_t			simulation_start_time;
	sem_t			*forks_sem;
	sem_t			*print_sem;
	sem_t			*dead_sem;
	sem_t			*meals_sem;
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
int			init_semaphores(t_data *data);
// monitor.c
void		*death_monitor_routine(void *philo_p);
bool		time_over(t_philo *philo);
// philo_main.c
int			main(int argc, char **argv);
// routine.c
void		philo_routine(t_philo *philo);
// processes.c
int			create_processes(t_data *data);
void		wait_for_processes(t_data *data);
// utils_02.c
size_t		get_time(void);
void		ft_usleep(size_t time);
void		print_death_msg(t_data *data, int id);
// utils.c
void		free_data(t_data *data);
void		print_msg(t_data *data, int id, char *msg);
void		set_philo_status(t_philo *philo, enum e_status status);
void		close_semaphores(t_data *data);
char		*ft_itoa(int n);
void		ft_strcat(char *dest, const char *src);
void		ft_strcpy(char *dest, const char *src);

#endif