/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:57:17 by samatsum          #+#    #+#             */
/*   Updated: 2025/01/19 12:45:50 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int			run_threads(t_data *data);
static int	philo_thread_create(t_data *data);
int			join_threads(t_data *data);

/* ************************************************************************** */
int	run_threads(t_data *data)
{
	if (philo_thread_create(data) == FAIL)
		return (FAIL);
	if (pthread_create(&data->monitor_all_alive, NULL,
			&all_alive_monitor_routine, data))
		return (FAIL);
	if (data->nb_must_meals > 0 && pthread_create(&data->monitor_all_full, NULL,
			&all_full_monitor_routine, data))
		return (FAIL);
	return (SUCCESS);
}

static int	philo_thread_create(t_data *data)
{
	int	index;

	index = -1;
	if ((data->nb_philos % 2 == 1) && (data->die_time < 3 * data->eat_time))
	{
		while (++index < data->nb_philos)
			if (pthread_create(&data->philo_ths[index], NULL, \
					&special_routine, &data->philos[index]))
				return (FAIL);
	}
	else
		while (++index < data->nb_philos)
			if (pthread_create(&data->philo_ths[index], NULL, \
					&routine, &data->philos[index]))
				return (FAIL);
	data->simulation_start_time = get_time();
	return (SUCCESS);
}

/* ************************************************************************** */
int	join_threads(t_data *data)
{
	int	index;

	index = -1;
	if (pthread_join(data->monitor_all_alive, NULL))
		return (FAIL);
	if (data->nb_must_meals > 0 && pthread_join(data->monitor_all_full, NULL))
		return (FAIL);
	while (++index < data->nb_philos)
	{
		if (pthread_join(data->philo_ths[index], NULL))
			return (FAIL);
	}
	return (SUCCESS);
}
