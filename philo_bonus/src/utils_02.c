/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:11:34 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/30 01:27:25 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_usleep(size_t sleep_time);
size_t	get_time(void);
void	print_death_msg(t_data *data, int id);

/* ************************************************************************** */
/* 時間関連の関数はほぼそのまま使用可能 */
void	ft_usleep(size_t sleep_time)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < sleep_time)
		usleep(10);
}

/* ************************************************************************** */
size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/* ************************************************************************** */
/* 死亡メッセージ表示関数はミューテックスからセマフォに変更 */
void	print_death_msg(t_data *data, int id)
{
	size_t	time;

	/* ミューテックスをセマフォに変更 */
	sem_wait(data->print_sem);
	time = get_time() - data->simulation_start_time;
	printf("%lu %d died\n", time, id);
	sem_post(data->print_sem);
	
	/* 死亡フラグも更新 */
	set_simulation_running(data, false);
}
