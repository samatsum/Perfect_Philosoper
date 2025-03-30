/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:57:17 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/30 17:01:39 by samatsum         ###   ########.fr       */
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
	int	index;
	pid_t pid;

	index = -1;
	main_data->simulation_start_time = 0;
	printf("STartttttttttttttttttttttttt!!!!!\n");
	main_data->simulation_start_time = get_time();
	while (++index < main_data->nb_philos)
	{
		pid = fork();
		if (pid < 0)
			return (FAIL);
		else if (pid == 0)
		{
			/* Child process (philosopher) */
			philosopher_routine(&main_data->philos[index], main_data);
			exit(0); /* Should never reach here due to exit in routine */
		}
		else
		{
			/* Parent process */
			main_data->philo_pids[index] = pid;
		}
	}
	return (SUCCESS);
}

/* ************************************************************************** */
int	wait_processes(t_data *main_data)
{
	int	status;
	
	/* Wait for death monitor */
	waitpid(main_data->monitor_pid, &status, 0);
	
	/* Wait for meal monitor if it exists */
	if (main_data->nb_must_meals > 0)
		waitpid(main_data->meal_monitor_pid, &status, 0);
	
	/* Ensure all philosopher processes are terminated */
	for (int i = 0; i < main_data->nb_philos; i++)
	{
		/* Send termination signal */
		kill(main_data->philo_pids[i], SIGTERM);
		/* Wait for process to exit */
		waitpid(main_data->philo_pids[i], &status, 0);
	}
	
	return (SUCCESS);
}