/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:57:17 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/30 01:23:52 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int			run_processes(t_data *data);
static int	create_philosopher_processes(t_data *data);
int			wait_processes(t_data *data);

/* ************************************************************************** */
int	run_processes(t_data *data)
{
	if (create_philosopher_processes(data) == FAIL)
		return (FAIL);
	
	/* 監視プロセスの作成 */
	if (create_monitor_process(data) == FAIL)
	{
		/* エラー発生時、哲学者プロセスを終了 */
		for (int i = 0; i < data->nb_philos; i++)
			kill(data->philo_pids[i], SIGTERM);
		return (FAIL);
	}
	
	return (SUCCESS);
}

/* ************************************************************************** */
static int	create_philosopher_processes(t_data *data)
{
	int	index;

	index = -1;
	data->simulation_start_time = get_time();
	
	while (++index < data->nb_philos)
	{
		data->philo_pids[index] = fork();
		if (data->philo_pids[index] < 0)
			return (FAIL);
		else if (data->philo_pids[index] == 0)
		{
			/* 子プロセス（哲学者）の処理 */
			philosopher_routine(&data->philos[index]);
			exit(0); /* 子プロセスは処理完了後に終了する */
		}
	}
	
	return (SUCCESS);
}

/* ************************************************************************** */
int	wait_processes(t_data *data)
{
	int	index;
	int	status;
	
	/* 親プロセスは子プロセスの終了を待つ */
	waitpid(data->monitor_pid, &status, 0);
	
	index = -1;
	while (++index < data->nb_philos)
	{
		/* すべての哲学者プロセスを待機 */
		waitpid(data->philo_pids[index], &status, 0);
	}
	
	return (SUCCESS);
}

/* ************************************************************************** */
int	create_monitor_process(t_data *data)
{
	data->monitor_pid = fork();
	
	if (data->monitor_pid < 0)
		return (FAIL);
	else if (data->monitor_pid == 0)
	{
		/* 子プロセス: 監視を担当 */
		
		/* 死亡通知を待つ */
		sem_wait(data->dead_sem);
		
		/* 死亡が検出された - すべての哲学者を終了させる */
		for (int i = 0; i < data->nb_philos; i++)
			kill(data->philo_pids[i], SIGTERM);
			
		exit(0);
	}
	
	return (SUCCESS);
}
