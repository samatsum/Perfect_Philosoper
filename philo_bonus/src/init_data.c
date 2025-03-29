/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 13:15:12 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/30 03:49:21 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int			init_semaphores(t_data *data);
int			init_philos(t_data *data);
int			init_data(t_data *data, int argc, char **argv);
static int	malloc_data(t_data *data);

/* ************************************************************************** */
/* ************************************************************************** */
int	init_semaphores(t_data *data)
{
	/* Remove any existing semaphores */
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_MEALS);
	sem_unlink(SEM_DATA);
	
	/* Create semaphores */
	data->forks_sem = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 0644, data->nb_philos);
	data->print_sem = sem_open(SEM_PRINT, O_CREAT | O_EXCL, 0644, 1);
	data->dead_sem = sem_open(SEM_DEAD, O_CREAT | O_EXCL, 0644, 0);
	data->meals_sem = sem_open(SEM_MEALS, O_CREAT | O_EXCL, 0644, 0);
	data->data_sem = sem_open(SEM_DATA, O_CREAT | O_EXCL, 0644, 1);
	
	if (data->forks_sem == SEM_FAILED || data->print_sem == SEM_FAILED ||
		data->dead_sem == SEM_FAILED || data->meals_sem == SEM_FAILED ||
		data->data_sem == SEM_FAILED)
		return (FAIL);
		
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
	
	data->philo_pids = malloc(sizeof(pid_t) * data->nb_philos);
	if (data->philo_pids == NULL)
	{
		free(data->philos);
		return (MALLOC_ERROR);
	}
	
	return (SUCCESS);
}

/* ************************************************************************** */
/* ************************************************************************** */
void	cleanup_semaphores(t_data *data)
{
	/* Close semaphores */
	sem_close(data->forks_sem);
	sem_close(data->print_sem);
	sem_close(data->dead_sem);
	sem_close(data->meals_sem);
	sem_close(data->data_sem);
	
	/* Unlink semaphores */
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_MEALS);
	sem_unlink(SEM_DATA);
}