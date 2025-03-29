/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 13:15:12 by samatsum          #+#    #+#             */
/*   Updated: 2025/01/19 14:40:39 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int			init_forks(t_data *data);
int			init_philos(t_data *data);
static void	usleep_time_calculater(int index, t_data *data);
int			init_data(t_data *data, int argc, char **argv);
static int	malloc_data(t_data *data);

/* ************************************************************************** */
int	init_forks(t_data *data)
{
	int		index;
	t_philo	*philos;

	philos = data->philos;
	index = -1;
	while (++index < data->nb_philos)
		pthread_mutex_init(&data->forks[index], NULL);
	index = 0;
	philos[0].left_f = &data->forks[0];
	philos[0].right_f = &data->forks[data->nb_philos - 1];
	while (++index < data->nb_philos)
	{
		philos[index].left_f = &data->forks[index];
		philos[index].right_f = &data->forks[index - 1];
	}
	return (SUCCESS);
}

/* ************************************************************************** */
int	init_philos(t_data *data)
{
	t_philo	*philos;
	int		index;

	index = -1;
	philos = data->philos;
	while (++index < data->nb_philos)
	{
		philos[index].data = data;
		philos[index].status = IDLE;
		philos[index].id = index + 1;
		philos[index].nb_meals_ate = 0;
		philos[index].last_eat_time = get_time();
		usleep_time_calculater(index, data);
	}
	return (SUCCESS);
}

static void	usleep_time_calculater(int index, t_data *data)
{
	t_philo	*philos;
	int		wave_index;

	philos = data->philos;
	if ((philos[index].id % 2) == 1)
	{
		wave_index = (philos[index].id - 1) / 2;
		philos[index].usleep_time = wave_index * data->eat_interval_time;
	}
	else
	{
		wave_index = (philos[index].id / 2) - 1;
		philos[index].usleep_time = (data->nb_odd_philos + wave_index) \
			* data->eat_interval_time;
	}
	if (philos[index].usleep_time >= (int)data->die_time)
		philos[index].usleep_time -= (int)data->die_time;
}

/* ************************************************************************** */
int	init_data(t_data *data, int argc, char **argv)
{
	data->simulation_start_time = 0;
	data->keep_iterating_flag = true;
	data->nb_philos = ft_atoi(argv[1]);
	data->die_time = (size_t)ft_atoi(argv[2]);
	data->eat_time = (size_t)ft_atoi(argv[3]);
	data->sleep_time = (size_t)ft_atoi(argv[4]);
	data->nb_must_meals = -1;
	if (argc == 6)
		data->nb_must_meals = ft_atoi(argv[5]);
	if (data->nb_philos > 2)
	{
		data->nb_odd_philos = (data->nb_philos + 1) / 2;
		data->eat_interval_time = data->eat_time / (data->nb_odd_philos - 1);
		if (data->eat_interval_time <= 0)
			data->eat_interval_time = 1;
	}
	else
	{
		data->nb_odd_philos = 0;
		data->eat_interval_time = 0;
	}
	pthread_mutex_init(&data->mutex_print, NULL);
	pthread_mutex_init(&data->mutex_keep_iter, NULL);
	return (malloc_data(data));
}

/* ************************************************************************** */
static int	malloc_data(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (data->philos == NULL)
		return (MALLOC_ERROR);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (data->forks == NULL)
	{
		free(data->philos);
		return (MALLOC_ERROR);
	}
	data->philo_ths = malloc(sizeof(pthread_t) * data->nb_philos);
	if (data->philo_ths == NULL)
	{
		free(data->philos);
		free(data->forks);
		return (MALLOC_ERROR);
	}
	return (SUCCESS);
}
