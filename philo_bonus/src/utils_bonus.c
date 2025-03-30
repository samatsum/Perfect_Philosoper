/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 11:46:56 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/30 18:52:19 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	free_data(t_data *main_data);
void	print_msg(t_data *p_data, int id, char *msg);
bool	get_simulation_running(t_data *p_data);
void	set_simulation_running(t_data *p_data, bool set_to);

/* ************************************************************************** */
void	free_data(t_data *main_data)
{
	free(main_data->philo_pids);
	free(main_data->philos);
}

/* ************************************************************************** */
void	print_msg(t_data *p_data, int id, char *msg)
{
	size_t	time;

	sem_wait(p_data->print_sem);
	time = get_time() - p_data->simulation_start_time;
	printf("%lu %d %s\n", time, id, msg);
	sem_post(p_data->print_sem);
}

/* ************************************************************************** */
bool	get_simulation_running(t_data *p_data)
{
	bool	running;

	running = p_data->keep_iterating_flag;
	return (running);
}

/* ************************************************************************** */
void	set_simulation_running(t_data *p_data, bool status)
{
	p_data->keep_iterating_flag = status;
}
