/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 21:09:44 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/30 01:24:32 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void		*philosopher_routine(void *philo_p);
static int	ft_think(t_philo *philo);
static int	ft_sleep(t_philo *philo);
void		*death_monitor(void *philo_p);

/* ************************************************************************** */
void	*philosopher_routine(void *philo_p)
{
	t_philo	*philo;
	pthread_t death_monitor_tid;

	philo = (t_philo *) philo_p;
	
	/* 哲学者プロセス内で死亡監視スレッドを作成 */
	if (pthread_create(&death_monitor_tid, NULL, &death_monitor, philo))
		exit(1);
	pthread_detach(death_monitor_tid);
	
	/* 最終食事時間を初期化 */
	philo->last_eat_time = philo->data->simulation_start_time;
	
	/* 偶数番号の哲学者は少し遅らせる（デッドロック防止） */
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->eat_time / 2);
	
	/* メインループ */
	while (1)
	{
		if (ft_eat(philo) == PHILO_DEATH)
			break;
		
		if (ft_sleep(philo) == PHILO_DEATH)
			break;
		
		if (ft_think(philo) == PHILO_DEATH)
			break;
	}
	
	exit(0); /* 哲学者プロセスの終了 */
}

/* ************************************************************************** */
void	*death_monitor(void *philo_p)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philo_p;
	data = philo->data;
	
	while (1)
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
static int	ft_think(t_philo *philo)
{
	print_msg(philo->data, philo->id, "is thinking");
	return (SUCCESS);
}

/* ************************************************************************** */
static int	ft_sleep(t_philo *philo)
{
	print_msg(philo->data, philo->id, "is sleeping");
	ft_usleep(philo->data->sleep_time);
	return (SUCCESS);
}
