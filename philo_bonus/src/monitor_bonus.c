/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:12:54 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/29 23:12:24 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void		*death_monitor_routine(void *philo_p);
bool		time_over(t_philo *philo);

/* ************************************************************************** */
void	*death_monitor_routine(void *philo_p)
{
	t_philo	*philo;
	t_data	*data;
	
	philo = (t_philo *)philo_p;
	data = philo->data;
	
	while (1)
	{
		// Check if this philosopher is dead
		if (time_over(philo))
		{
			// Signal that a philosopher has died
			print_death_msg(data, philo->id);
			sem_post(data->dead_sem);
			break;
		}
		
		// Check if we should terminate
		if (sem_trywait(data->dead_sem) == 0)
		{
			// Someone else has died, propagate the signal
			sem_post(data->dead_sem);
			break;
		}
		
		// Wait a bit before checking again
		usleep(1000);
	}
	return (NULL);
}

/* ************************************************************************** */
bool	time_over(t_philo *philo)
{
	bool	result;
	t_data	*data;
	
	data = philo->data;
	result = false;
	
	// Check if philosopher has starved
	sem_wait(philo->philo_dead_sem);
	if ((get_time() - philo->last_eat_time) > data->die_time)
	{
		set_philo_status(philo, DEAD);
		result = true;
	}
	sem_post(philo->philo_dead_sem);
	
	return (result);
}
