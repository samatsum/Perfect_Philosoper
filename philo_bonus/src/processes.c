/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:57:17 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/30 03:54:45 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int			run_processes(t_data *data);
static int	create_philosopher_processes(t_data *data);
int			wait_processes(t_data *data);

/* ************************************************************************** */
int	run_processes(t_data *data)
{
	data->simulation_start_time = get_time();
	
	if (create_philosopher_processes(data) == FAIL)
		return (FAIL);
	
	return (SUCCESS);
}

/* ************************************************************************** */
static int	create_philosopher_processes(t_data *data)
{
	int	index;
	pid_t pid;

	index = -1;
	while (++index < data->nb_philos)
	{
		pid = fork();
		if (pid < 0)
			return (FAIL);
		else if (pid == 0)
		{
			/* Child process (philosopher) */
			philosopher_routine(&data->philos[index]);
			exit(0); /* Should never reach here due to exit in routine */
		}
		else
		{
			/* Parent process */
			data->philo_pids[index] = pid;
		}
	}
	
	return (SUCCESS);
}

/* ************************************************************************** */
int	wait_processes(t_data *data)
{
	int	status;
	
	/* Wait for death monitor */
	waitpid(data->monitor_pid, &status, 0);
	
	/* Wait for meal monitor if it exists */
	if (data->nb_must_meals > 0)
		waitpid(data->meal_monitor_pid, &status, 0);
	
	/* Ensure all philosopher processes are terminated */
	for (int i = 0; i < data->nb_philos; i++)
	{
		/* Send termination signal */
		kill(data->philo_pids[i], SIGTERM);
		/* Wait for process to exit */
		waitpid(data->philo_pids[i], &status, 0);
	}
	
	return (SUCCESS);
}