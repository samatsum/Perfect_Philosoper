/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 13:15:12 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/30 17:01:39 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int			init_semaphores(t_data *main_data);
int			init_philos(t_data *main_data);
int			init_data(t_data *main_data, int argc, char **argv);
static int	malloc_data(t_data *main_data);

/* ************************************************************************** */
/* ************************************************************************** */
int	init_semaphores(t_data *main_data)
{
	/* Remove any existing semaphores */
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_MEALS);
	sem_unlink(SEM_DATA);
	/* Create semaphores */
	main_data->forks_sem = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 0644, main_data->nb_philos);
	main_data->print_sem = sem_open(SEM_PRINT, O_CREAT | O_EXCL, 0644, 1);
	main_data->dead_sem = sem_open(SEM_DEAD, O_CREAT | O_EXCL, 0644, 0);
	main_data->meals_sem = sem_open(SEM_MEALS, O_CREAT | O_EXCL, 0644, 0);
	main_data->data_sem = sem_open(SEM_DATA, O_CREAT | O_EXCL, 0644, 1);
	if (main_data->forks_sem == SEM_FAILED || main_data->print_sem == SEM_FAILED ||
		main_data->dead_sem == SEM_FAILED || main_data->meals_sem == SEM_FAILED ||
		main_data->data_sem == SEM_FAILED)
		return (FAIL);
	return (SUCCESS);
}
/* ************************************************************************** */
int	init_philos(t_data *main_data)
{
	t_philo	*philos;
	int		index;

	index = -1;
	philos = main_data->philos;
	while (++index < main_data->nb_philos)
	{
		philos[index].philo_data = main_data;
		philos[index].status = IDLE;
		philos[index].id = index + 1;
		philos[index].nb_meals_ate = 0;
		philos[index].last_eat_time = get_time();
	}
	return (SUCCESS);
}

/* ************************************************************************** */
int	init_data(t_data *main_data, int argc, char **argv)
{
	main_data->simulation_start_time = 0;
	main_data->keep_iterating_flag = true;
	main_data->nb_philos = ft_atoi(argv[1]);
	main_data->die_time = (size_t)ft_atoi(argv[2]);
	main_data->eat_time = (size_t)ft_atoi(argv[3]);
	main_data->sleep_time = (size_t)ft_atoi(argv[4]);
	main_data->nb_must_meals = -1;
	if (argc == 6)
		main_data->nb_must_meals = ft_atoi(argv[5]);
	return (malloc_data(main_data));
}

/* ************************************************************************** */
static int	malloc_data(t_data *main_data)
{
	main_data->philos = malloc(sizeof(t_philo) * main_data->nb_philos);
	if (main_data->philos == NULL)
		return (MALLOC_ERROR);
	main_data->philo_pids = malloc(sizeof(pid_t) * main_data->nb_philos);
	if (main_data->philo_pids == NULL)
	{
		free(main_data->philos);
		return (MALLOC_ERROR);
	}
	return (SUCCESS);
}

/* ************************************************************************** */
/* ************************************************************************** */
void	cleanup_semaphores(t_data *main_data)
{
	/* Close semaphores */
	sem_close(main_data->forks_sem);
	sem_close(main_data->print_sem);
	sem_close(main_data->dead_sem);
	sem_close(main_data->meals_sem);
	sem_close(main_data->data_sem);
	
	/* Unlink semaphores */
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_MEALS);
	sem_unlink(SEM_DATA);
}
