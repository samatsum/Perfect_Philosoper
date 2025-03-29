/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 13:15:12 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/29 23:10:12 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int			init_semaphores(t_data *data);
int			init_philos(t_data *data);
int			init_data(t_data *data, int argc, char **argv);
static int	malloc_data(t_data *data);

/* ************************************************************************** */
int	init_semaphores(t_data *data)
{
	// Unlink any existing semaphores first
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_MEALS);

	// Create new semaphores
	data->forks_sem = sem_open(SEM_FORKS, O_CREAT, 0644, data->nb_philos);
	if (data->forks_sem == SEM_FAILED)
		return (FAIL);

	data->print_sem = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	if (data->print_sem == SEM_FAILED)
		return (FAIL);

	data->dead_sem = sem_open(SEM_DEAD, O_CREAT, 0644, 0);
	if (data->dead_sem == SEM_FAILED)
		return (FAIL);

	if (data->nb_must_meals > 0)
	{
		data->meals_sem = sem_open(SEM_MEALS, O_CREAT, 0644, 0);
		if (data->meals_sem == SEM_FAILED)
			return (FAIL);
	}
	
	return (SUCCESS);
}

/* ************************************************************************** */
int	init_philos(t_data *data)
{
	int		i;
	char	*num_str;
	
	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].data = data;
		data->philos[i].status = IDLE;
		data->philos[i].id = i + 1;
		data->philos[i].nb_meals_ate = 0;
		data->philos[i].last_eat_time = get_time();
		
		// Create a unique semaphore name for this philosopher
		ft_strcpy(data->philos[i].philo_dead_sem_name, SEM_PHILO_DEAD);
		num_str = ft_itoa(i + 1);
		if (!num_str)
			return (FAIL);
		ft_strcat(data->philos[i].philo_dead_sem_name, num_str);
		free(num_str);
		
		// Unlink existing semaphore if any
		sem_unlink(data->philos[i].philo_dead_sem_name);
		
		// Create a semaphore for death monitoring
		data->philos[i].philo_dead_sem = sem_open(
			data->philos[i].philo_dead_sem_name, O_CREAT, 0644, 1);
		if (data->philos[i].philo_dead_sem == SEM_FAILED)
			return (FAIL);
		
		i++;
	}
	return (SUCCESS);
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
	
	return (malloc_data(data));
}

/* ************************************************************************** */
static int	malloc_data(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (data->philos == NULL)
		return (MALLOC_ERROR);
	
	return (SUCCESS);
}
