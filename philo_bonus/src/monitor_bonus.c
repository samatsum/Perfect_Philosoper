/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:15:12 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/30 19:42:17 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void *death_monitor(void *philo_p);
int create_monitor_processes(t_data *main_data);
static void monitor_meals(t_data *main_data);

/* ************************************************************************** */
/* Death monitoring thread within each philosopher process */
void	*death_monitor(void *philo_p)
{
	t_philo	*philo = (t_philo *)philo_p;
	t_data	*p_data = philo->philo_data;

	while (get_simulation_running(p_data))
	{
		/* Check death condition */
		if ((get_time() - philo->last_eat_time) > p_data->die_time)
		{
			set_simulation_running(p_data, false);
			print_death_msg(p_data, philo->id);
			sem_post(p_data->dead_sem);
			exit(1);
		}
		// usleep(1000);
	}
	return (NULL);
}

/* ************************************************************************** */
/* Create separate processes for monitoring death and meal completion */
int	create_monitor_processes(t_data *main_data)
{
	/* Create death monitor process */
	main_data->create_monitor_pid = fork();
	if (main_data->create_monitor_pid < 0)
		return (FAIL);
	else if (main_data->create_monitor_pid == 0)
	{
		/* Death monitor process */
		sem_wait(main_data->dead_sem); /* Wait for death signal */
		/* Terminate all philosophers */
		for (int i = 0; i < main_data->nb_philos; i++)
			kill(main_data->philo_pids[i], SIGTERM);
		if (main_data->nb_must_meals > 0)
			kill(main_data->meal_monitor_pid, SIGTERM);
		exit(0);
	}
	/* Create meal monitor process if needed */
	if (main_data->nb_must_meals > 0)
	{
		main_data->meal_monitor_pid = fork();
		if (main_data->meal_monitor_pid < 0)
		{
			kill(main_data->create_monitor_pid, SIGTERM);
			return (FAIL);
		}
		else if (main_data->meal_monitor_pid == 0)
		{
			/* Meal monitor process */
			monitor_meals(main_data);
			exit(0); /* Should never reach here */
		}
	}
	return (SUCCESS);
}

/* ************************************************************************** */
/* Monitor meal completion - runs in its own process */
static void	monitor_meals(t_data *main_data)
{
	int	completed_meals = 0;

	/* Wait for meal completion signals from all philosophers */
	while (completed_meals < main_data->nb_philos)
	{
		sem_wait(main_data->meals_sem);
		printf("Monitor_Meals!!!!!!!!!!\n");
		completed_meals++;
	}
	sem_post(main_data->dead_sem);
}
