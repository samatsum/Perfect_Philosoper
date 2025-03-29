/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 11:46:56 by samatsum          #+#    #+#             */
/*   Updated: 2025/01/19 14:27:07 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_data(t_data *data);
void	print_msg(t_data *data, int id, char *msg);
bool	get_keep_iterating_flag(t_data *data);
void	set_keep_iterating_flag(t_data *data, bool set_to);
void	set_philo_status(t_philo *philo, enum e_status status);

/* ************************************************************************** */
void	free_data(t_data *data)
{
	int	index;

	index = -1;
	while (++index < data->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[index]);
	}
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_keep_iter);
	free(data->philo_ths);
	free(data->philos);
	free(data->forks);
}

/* ************************************************************************** */
void	print_msg(t_data *data, int id, char *msg)
{
	size_t	time;

	pthread_mutex_lock(&data->mutex_print);
	time = get_time() - data->simulation_start_time;
	if (get_keep_iterating_flag(data))
		printf("%lu %d %s\n", time, id, msg);
	pthread_mutex_unlock(&data->mutex_print);
}

/* ************************************************************************** */
bool	get_keep_iterating_flag(t_data *data)
{
	bool	iterating_flag;

	pthread_mutex_lock(&data->mutex_keep_iter);
	iterating_flag = data->keep_iterating_flag;
	pthread_mutex_unlock(&data->mutex_keep_iter);
	return (iterating_flag);
}

/* ************************************************************************** */
void	set_keep_iterating_flag(t_data *data, bool new_flag)
{
	pthread_mutex_lock(&data->mutex_keep_iter);
	data->keep_iterating_flag = new_flag;
	pthread_mutex_unlock(&data->mutex_keep_iter);
}

/* ************************************************************************** */
void	set_philo_status(t_philo *philo, enum e_status new_status)
{
	if (philo->status != DEAD)
		philo->status = new_status;
}
