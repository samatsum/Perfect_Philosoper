/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:12:54 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/30 01:10:52 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// 死亡監視プロセス
void *death_monitor(void *philo_p)
{
	t_philo *philo = (t_philo *)philo_p;
	t_data *data = philo->data;
	
	while (1)
	{
		if ((get_time() - philo->last_eat_time) > data->die_time)
		{
			// 死亡メッセージを出力
			sem_wait(data->print_sem);
			printf("%lu %d died\n", get_time() - data->simulation_start_time, philo->id);
			
			// 死亡を通知
			sem_post(data->dead_sem);
			return (NULL);
		}
		usleep(1000);  // 少し待機してCPU負荷を下げる
	}
}

// メイン監視プロセス
int create_monitor_process(t_data *data)
{
	data->monitor_pid = fork();
	
	if (data->monitor_pid < 0)
		return (FAIL);
	else if (data->monitor_pid == 0)
	{
		// 子プロセス: 監視を担当
		
		// 死亡通知を待つ
		sem_wait(data->dead_sem);
		
		// 死亡が検出された - すべての哲学者を終了させる
		for (int i = 0; i < data->nb_philos; i++)
			kill(data->philo_pids[i], SIGTERM);
			
		exit(0);
	}
	
	return (SUCCESS);
}

// 食事完了監視
int monitor_meals(t_data *data)
{
	if (data->nb_must_meals <= 0)
		return (SUCCESS);  // 食事回数指定なし
		
	for (int i = 0; i < data->nb_philos; i++)
		sem_wait(data->meals_sem);  // 各哲学者からの食事完了通知を待つ
		
	// すべての哲学者が食事を完了 - シミュレーション終了
	for (int i = 0; i < data->nb_philos; i++)
		kill(data->philo_pids[i], SIGTERM);
		
	// 監視プロセスも終了
	kill(data->monitor_pid, SIGTERM);
	
	return (SUCCESS);
}
