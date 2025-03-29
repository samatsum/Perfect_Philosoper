/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 11:46:56 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/30 03:54:54 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_data(t_data *data);
void	print_msg(t_data *data, int id, char *msg);
bool	get_simulation_running(t_data *data);
void	set_simulation_running(t_data *data, bool set_to);

/* ************************************************************************** */
void	free_data(t_data *data)
{
	free(data->philo_pids);
	free(data->philos);
}

/* ************************************************************************** */
void	print_msg(t_data *data, int id, char *msg)
{
	size_t	time;

	if (!get_simulation_running(data))
		return;
		
	sem_wait(data->print_sem);
	time = get_time() - data->simulation_start_time;
	printf("%lu %d %s\n", time, id, msg);
	sem_post(data->print_sem);
}

/* ************************************************************************** */
bool	get_simulation_running(t_data *data)
{
	bool	running;

	sem_wait(data->data_sem);
	running = data->keep_iterating_flag;
	sem_post(data->data_sem);
	
	return (running);
}

/* ************************************************************************** */
void	set_simulation_running(t_data *data, bool status)
{
	sem_wait(data->data_sem);
	data->keep_iterating_flag = status;
	sem_post(data->data_sem);
}