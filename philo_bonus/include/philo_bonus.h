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
# include <semaphore.h> /* 追加: セマフォ用ヘッダー */
# include <fcntl.h>     /* 追加: O_CREAT等のフラグ用 */
# include <sys/stat.h>  /* 追加: セマフォのパーミッション用 */
# include <sys/wait.h>  /* 追加: waitpid用 */
# include <signal.h>    /* 追加: kill用 */

# define SUCCESS 0
# define INPUT_OK 0
# define FAIL 1
# define PHILO_DEATH 1

# define ALL_OK 0
# define WRONG_INPUT 1
# define MALLOC_ERROR 2

/* セマフォ名の定義 */
# define SEM_START "/philo_start"
# define SEM_FORKS "/philo_forks"
# define SEM_PRINT "/philo_print"
# define SEM_DEAD "/philo_dead"
# define SEM_MEALS "/philo_meals"
# define SEM_DATA "/philo_data"

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
	t_data			*philo_data;
	enum e_status	status;
	size_t			last_eat_time;
	/* 以下の行を削除（フォークは中央で管理するためポインタ不要）
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	pthread_mutex_t	mutex_last_eat_time; */
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


	sem_t			*start_sem;
	/* 以下のミューテックスをセマフォに置き換え */
	sem_t			*forks_sem;       /* 利用可能なフォークの数 */
	sem_t			*print_sem;       /* 出力保護用 */
	sem_t			*dead_sem;        /* 死亡通知用 */
	sem_t			*meals_sem;       /* 食事完了通知用 */
	sem_t			*data_sem;        /* データアクセス保護用 */

	/* スレッドをプロセスに置き換え */
	pid_t			*philo_pids;      /* 哲学者プロセスID配列 */
	pid_t			create_monitor_pid;
	pid_t			meal_monitor_pid; /* Added this field */
	/* 削除：これらは不要になる
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_keep_iter;
	pthread_t		monitor_all_alive;
	pthread_t		monitor_all_full;
	pthread_t		*philo_ths;
	pthread_mutex_t	*forks; */

	t_philo			*philos;
}t_data;

/* 既存の関数宣言は維持 */
int			check_input(int argc, char **argv);
int			ft_atoi(char *str);
int			ft_eat(t_philo *philo);
int			init_data(t_data *data, int argc, char **argv);
int			init_philos(t_data *data);

/* 以下の関数宣言を変更 */
int			init_semaphores(t_data *data);  /* init_forks の代わり */
void		*philosopher_routine(void *philo_p, t_data *data);  /* routine の代わり */
int			run_processes(t_data *data);  /* run_threads の代わり */
int			wait_processes(t_data *data);  /* join_threads の代わり */
void		cleanup_semaphores(t_data *data);  /* 新規追加 */

/* 監視関数の変更 */
int			create_monitor_process(t_data *data);
void		*death_monitor(void *philo_p);

/* 既存のユーティリティ関数は維持 */
size_t		get_time(void);
void		print_msg(t_data *data, int id, char *msg);
void		print_death_msg(t_data *data, int id);
void		free_data(t_data *data);
int			create_monitor_processes(t_data *data);

/* 以下の関数名を変更（内部実装もセマフォベースに変更） */
bool		get_simulation_running(t_data *data);  /* get_keep_iterating_flag の代わり */
void		set_simulation_running(t_data *data, bool status);  /* set_keep_iterating_flag の代わり */

#endif