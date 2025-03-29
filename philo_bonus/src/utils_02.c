/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:11:34 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/30 03:41:02 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_usleep(size_t sleep_time);
size_t	get_time(void);
void	print_death_msg(t_data *data, int id);

/* ************************************************************************** */
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
void	print_death_msg(t_data *data, int id)
{
	size_t	time;
	static int	death_reported = 0;

	sem_wait(data->print_sem);
	/* 死亡が既に報告されているか確認 */
	if (death_reported == 0)
	{
		time = get_time() - data->simulation_start_time;
		printf("%lu %d died\n", time, id);
		death_reported = 1;
	}
	sem_post(data->print_sem);
	
	/* 死亡フラグを設定（セマフォ保護付き） */
	set_simulation_running(data, false);
}