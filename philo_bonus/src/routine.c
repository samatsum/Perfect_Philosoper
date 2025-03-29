/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 21:09:44 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/30 03:48:26 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void		*philosopher_routine(void *philo_p);
static int	ft_think(t_philo *philo);
static int	ft_sleep(t_philo *philo);

/* ************************************************************************** */
void	*philosopher_routine(void *philo_p)
{
	t_philo	*philo;
	pthread_t death_tid;

	philo = (t_philo *)philo_p;
	
	/* Initialize last_eat_time at start of simulation */
	philo->last_eat_time = philo->data->simulation_start_time;
	
	/* Create death monitor thread */
	if (pthread_create(&death_tid, NULL, &death_monitor, philo))
		exit(1);
	pthread_detach(death_tid);
	
	/* Add delay for even-numbered philosophers to avoid deadlock */
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->eat_time / 2);
	
	/* Main lifecycle loop */
	while (get_simulation_running(philo->data))
	{
		if (ft_eat(philo) == PHILO_DEATH)
			break;
		
		if (!get_simulation_running(philo->data))
			break;
			
		if (ft_sleep(philo) == PHILO_DEATH)
			break;
		
		if (!get_simulation_running(philo->data))
			break;
			
		if (ft_think(philo) == PHILO_DEATH)
			break;
	}
	
	exit(0);
}

/* ************************************************************************** */
static int	ft_think(t_philo *philo)
{
	if (get_simulation_running(philo->data))
		print_msg(philo->data, philo->id, "is thinking");
	return (SUCCESS);
}

/* ************************************************************************** */
static int	ft_sleep(t_philo *philo)
{
	if (get_simulation_running(philo->data))
	{
		print_msg(philo->data, philo->id, "is sleeping");
		ft_usleep(philo->data->sleep_time);
	}
	return (SUCCESS);
}
