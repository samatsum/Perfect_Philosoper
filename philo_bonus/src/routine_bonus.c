/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 21:09:44 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/29 23:10:47 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void		philo_routine(t_philo *philo);
static int	ft_think(t_philo *philo);
static int	ft_sleep(t_philo *philo);

/* ************************************************************************** */
void	philo_routine(t_philo *philo)
{
	pthread_t	monitor_thread;

	// Create a monitor thread for this philosopher
	if (pthread_create(&monitor_thread, NULL, death_monitor_routine, philo) != 0)
		exit(1);
	pthread_detach(monitor_thread);

	// Even-numbered philosophers wait a bit to prevent deadlock
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->eat_time / 2);

	// Main routine loop
	while (1)
	{
		if (ft_eat(philo) == PHILO_DEATH)
			break;
		if (ft_sleep(philo) == PHILO_DEATH)
			break;
		if (ft_think(philo) == PHILO_DEATH)
			break;
	}

	// Exit the process
	exit(0);
}

/* ************************************************************************** */
static int	ft_think(t_philo *philo)
{
	set_philo_status(philo, THINKING);
	if (philo->status == DEAD)
		return (PHILO_DEATH);
	print_msg(philo->data, philo->id, "is thinking");
	return (SUCCESS);
}

/* ************************************************************************** */
static int	ft_sleep(t_philo *philo)
{
	set_philo_status(philo, SLEEPING);
	if (philo->status == DEAD)
		return (PHILO_DEATH);
	print_msg(philo->data, philo->id, "is sleeping");
	ft_usleep(philo->data->sleep_time);
	return (SUCCESS);
}
