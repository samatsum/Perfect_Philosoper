/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_02_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:11:34 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/30 18:10:30 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

size_t	get_time(void);
void	print_death_msg(t_data *p_data, int id);

/* ************************************************************************** */
size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/* ************************************************************************** */
void	print_death_msg(t_data *p_data, int id)
{
	size_t	time;

	sem_wait(p_data->print_sem);
	time = get_time() - p_data->simulation_start_time;
	printf("%lu %d died\n", time, id);
	sem_post(p_data->print_sem);
}
