/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:12:54 by samatsum          #+#    #+#             */
/*   Updated: 2025/01/19 14:25:29 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void		*all_full_monitor_routine(void *data_p);
static bool	check_all_philos_full(t_data *data);
void		*all_alive_monitor_routine(void *data_p);
bool		time_over(t_philo *philo);
static void	notify_all_philos(t_data *data);

/* ************************************************************************** */
// usleep(1000) for ALL philosophers sleeping
void	*all_full_monitor_routine(void *data_p)
{
	t_data	*data;

	data = (t_data *)data_p;
	while (get_keep_iterating_flag(data))
	{
		usleep(1000);
		if (check_all_philos_full(data) == SUCCESS)
			break ;
	}
	if (get_keep_iterating_flag(data))
	{
		set_keep_iterating_flag(data, false);
		notify_all_philos(data);
	}
	return (NULL);
}

/* ************************************************************************** */
static bool	check_all_philos_full(t_data *data)
{
	int	index;
	int	full_flag;

	index = -1;
	full_flag = 1;
	while (++index < data->nb_philos && get_keep_iterating_flag(data))
	{
		full_flag *= (data->philos[index].nb_meals_ate >= data->nb_must_meals);
		if (full_flag == 0)
			return (FAIL);
	}
	return (SUCCESS);
}

/* ************************************************************************** */
void	*all_alive_monitor_routine(void *data_p)
{
	int		index;
	t_data	*data;
	t_philo	*philos;

	data = (t_data *)data_p;
	philos = data->philos;
	index = -1;
	while (++index < data->nb_philos && get_keep_iterating_flag(data))
	{
		if (time_over(&philos[index]) && get_keep_iterating_flag(data))
		{
			set_keep_iterating_flag(data, false);
			notify_all_philos(data);
			print_death_msg(data, philos[index].id);
			break ;
		}
		if (index == data->nb_philos - 1)
			index = -1;
	}
	return (NULL);
}

/* ************************************************************************** */
bool	time_over(t_philo *philo)
{
	bool		result;
	t_data		*data;

	data = philo->data;
	result = false;
	if ((get_time() - philo->last_eat_time) > data->die_time)
	{
		set_philo_status(philo, DEAD);
		result = true;
	}
	return (result);
}

/* ************************************************************************** */
static void	notify_all_philos(t_data *data)
{
	t_philo	*philos;
	int		index;

	philos = data->philos;
	index = -1;
	while (++index < data->nb_philos)
		set_philo_status(&philos[index], DEAD);
}
