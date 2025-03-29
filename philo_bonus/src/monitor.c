/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:15:12 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/30 03:53:17 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void *death_monitor(void *philo_p);
int create_monitor_processes(t_data *data);
static void monitor_meals(t_data *data);

/* ************************************************************************** */
/* Death monitoring thread within each philosopher process */
void *death_monitor(void *philo_p)
{
	t_philo *philo = (t_philo *)philo_p;
	t_data *data = philo->data;
	
	while (get_simulation_running(data))
	{
		/* Check death condition */
		if ((get_time() - philo->last_eat_time) > data->die_time)
		{
			sem_wait(data->print_sem);
			printf("%lu %d died\n", get_time() - data->simulation_start_time, philo->id);
			sem_post(data->print_sem);
			
			/* Signal death */
			sem_post(data->dead_sem);
			exit(1); /* Exit immediately */
		}
		usleep(1000);
	}
	return (NULL);
}

/* ************************************************************************** */
/* Create separate processes for monitoring death and meal completion */
int create_monitor_processes(t_data *data)
{
	/* Create death monitor process */
	data->monitor_pid = fork();
	if (data->monitor_pid < 0)
		return (FAIL);
	else if (data->monitor_pid == 0)
	{
		/* Death monitor process */
		sem_wait(data->dead_sem); /* Wait for death signal */
		
		/* Terminate all philosophers */
		set_simulation_running(data, false);
		for (int i = 0; i < data->nb_philos; i++)
			kill(data->philo_pids[i], SIGTERM);
		
		exit(0);
	}
	
	/* Create meal monitor process if needed */
	if (data->nb_must_meals > 0)
	{
		data->meal_monitor_pid = fork();
		if (data->meal_monitor_pid < 0)
		{
			kill(data->monitor_pid, SIGTERM);
			return (FAIL);
		}
		else if (data->meal_monitor_pid == 0)
		{
			/* Meal monitor process */
			monitor_meals(data);
			exit(0); /* Should never reach here */
		}
	}
	
	return (SUCCESS);
}

/* ************************************************************************** */
/* Monitor meal completion - runs in its own process */
static void monitor_meals(t_data *data)
{
	int completed_meals = 0;
	
	/* Wait for meal completion signals from all philosophers */
	while (completed_meals < data->nb_philos)
	{
		sem_wait(data->meals_sem);
		completed_meals++;
	}
	
	/* All philosophers have completed their meals */
	sem_wait(data->print_sem);
	printf("All philosophers have eaten at least %d times. Simulation completed.\n", 
		data->nb_must_meals);
	sem_post(data->print_sem);
	
	/* Signal termination */
	set_simulation_running(data, false);
	sem_post(data->dead_sem); /* Use death signal to trigger termination */
	
	/* Terminate all philosophers */
	for (int i = 0; i < data->nb_philos; i++)
		kill(data->philo_pids[i], SIGTERM);
	
	/* Also terminate the death monitor */
	kill(data->monitor_pid, SIGTERM);
	exit(0);
}