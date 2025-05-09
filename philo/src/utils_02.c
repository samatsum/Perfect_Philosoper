/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:11:34 by samatsum          #+#    #+#             */
/*   Updated: 2025/01/19 12:45:01 by samatsum         ###   ########.fr       */
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

	pthread_mutex_lock(&data->mutex_print);
	time = get_time() - data->simulation_start_time;
	printf("%lu %d died\n", time, id);
	pthread_mutex_unlock(&data->mutex_print);
}
