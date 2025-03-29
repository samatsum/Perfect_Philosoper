/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:15:12 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/30 03:40:23 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void		*death_monitor(void *philo_p);
int			create_monitor_process(t_data *data);
static void	monitor_meals(t_data *data);

/* ************************************************************************** */
/* 哲学者プロセス内の死亡監視スレッド */
void	*death_monitor(void *philo_p)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philo_p;
	data = philo->data;
	
	while (get_simulation_running(data))
	{
		/* 死亡条件のチェック */
		if ((get_time() - philo->last_eat_time) > data->die_time)
		{
			/* 死亡メッセージを出力 */
			print_death_msg(data, philo->id);
			
			/* 死亡を通知 */
			sem_post(data->dead_sem);
			break;
		}
		usleep(1000); /* 少し待機 */
	}
	
	return (NULL);
}

/* ************************************************************************** */
/* メイン監視プロセス */
int	create_monitor_process(t_data *data)
{
	data->monitor_pid = fork();
	
	if (data->monitor_pid < 0)
		return (FAIL);
	else if (data->monitor_pid == 0)
	{
		/* 子プロセス: 監視を担当 */
		
		/* 必要食事回数がある場合、別スレッドで食事完了を監視 */
		if (data->nb_must_meals > 0)
		{
			pthread_t meal_tid;
			
			if (pthread_create(&meal_tid, NULL, 
					(void *(*)(void *))monitor_meals, data))
				exit(1);
			pthread_detach(meal_tid);
		}
		
		/* 死亡通知を待つ */
		sem_wait(data->dead_sem);
		
		/* シミュレーション終了フラグを設定 */
		set_simulation_running(data, false);
		
		/* すべての哲学者プロセスを終了 */
		for (int i = 0; i < data->nb_philos; i++)
			kill(data->philo_pids[i], SIGTERM);
			
		exit(0);
	}
	
	return (SUCCESS);
}

/* ************************************************************************** */
/* 食事完了監視 - 監視プロセス内のスレッドとして実行 */
static void	monitor_meals(t_data *data)
{
	int	i;
	
	/* 各哲学者からの食事完了通知を待つ */
	for (i = 0; i < data->nb_philos; i++)
		sem_wait(data->meals_sem);
	
	/* シミュレーション終了フラグを設定 */
	set_simulation_running(data, false);
	
	/* 死亡監視にも通知 - プロセス終了のため */
	sem_post(data->dead_sem);
}
