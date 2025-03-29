
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:00:00 by samatsum          #+#    #+#             */
/*   Updated: 2025/01/20 10:00:00 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int			create_processes(t_data *data);
void		wait_for_processes(t_data *data);
static void	create_monitor_process(t_data *data);

/* ************************************************************************** */
int	create_processes(t_data *data)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < data->nb_philos)
	{
		pid = fork();
		if (pid == -1)
		{
			// Kill all children if one fork fails
			while (--i >= 0)
				kill(data->philos[i].pid, SIGKILL);
			return (FAIL);
		}
		if (pid == 0)
		{
			// Child process - philosopher
			data->philos[i].last_eat_time = get_time();
			philo_routine(&data->philos[i]);
			exit(0);
		}
		else
		{
			// Parent process - store child pid
			data->philos[i].pid = pid;
		}
		i++;
	}
	create_monitor_process(data);
	return (SUCCESS);
}

/* ************************************************************************** */
static void	create_monitor_process(t_data *data)
{
	pthread_t	monitor_thread;
	int			i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_create(&monitor_thread, NULL, death_monitor_routine, 
						&data->philos[i]) != 0)
			return ;
		pthread_detach(monitor_thread);
		i++;
	}
}

/* ************************************************************************** */
void	wait_for_processes(t_data *data)
{
	int	i;
	int	status;

	// Wait for any child to exit
	waitpid(-1, &status, 0);
	
	// Once one exits, kill all processes
	i = 0;
	while (i < data->nb_philos)
	{
		kill(data->philos[i].pid, SIGKILL);
		i++;
	}
}
