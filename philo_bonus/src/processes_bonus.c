/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:57:17 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/30 19:20:07 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int			run_processes(t_data *main_data);
static int	create_philosopher_processes(t_data *main_data);
int			wait_processes(t_data *main_data);

/* ************************************************************************** */
int	run_processes(t_data *main_data)
{
	if (create_philosopher_processes(main_data) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

/* ************************************************************************** */
static int	create_philosopher_processes(t_data *main_data)
{
	int		index;
	pid_t	pid;

	index = -1;
	main_data->simulation_start_time = get_time();
	while (++index < main_data->nb_philos)
	{
		pid = fork();
		if (pid < 0)
			return (FAIL);
		else if (pid == 0)
		{
			philosopher_routine(&main_data->philos[index], main_data);
			exit(0);
		}
		else
			main_data->philo_pids[index] = pid;
	}
	for (int i = 0; i < main_data->nb_philos; i++)
		sem_post(main_data->start_sem);
	return (SUCCESS);
}

/* ************************************************************************** */
int	wait_processes(t_data *main_data)
{
	int	status;

	waitpid(main_data->create_monitor_pid, &status, 0);
	printf("End The Create_Monitor\n");
	/* Wait for meal monitor if it exists */
	if (main_data->nb_must_meals > 0)
		waitpid(main_data->meal_monitor_pid, &status, 0);
	printf("End The Meal_Monitor\n");
	/* Ensure all philosopher processes are terminated */
	for (int i = 0; i < main_data->nb_philos; i++)
	{
		// /* Send termination signal */
		// kill(main_data->philo_pids[i], SIGTERM);
		// /* Wait for process to exit */
		waitpid(main_data->philo_pids[i], &status, 0);
	}
	printf("End The Wait_Process\n");
	return (SUCCESS);
}