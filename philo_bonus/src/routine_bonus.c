/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 21:09:44 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/30 20:13:18 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void		*philosopher_routine(void *philo_p, t_data *main_data);
static int	ft_think(t_philo *philo);
static int	ft_sleep(t_philo *philo);

/* ************************************************************************** */
void	*philosopher_routine(void *philo_p, t_data *main_data)
{
	t_philo		*philo;
	pthread_t	death_tid;

	philo = (t_philo *)philo_p;

	philo->philo_data->simulation_start_time = main_data->simulation_start_time;
	philo->last_eat_time = main_data->simulation_start_time;
	philo->philo_data = main_data;
	if (pthread_create(&death_tid, NULL, &death_monitor, philo))
		exit(1);
	pthread_detach(death_tid);
	sem_wait(main_data->start_sem);
	if (philo->id % 2 == 0)
		usleep(philo->philo_data->eat_time * 1000);
	/* Main lifecycle loop */
	while (get_simulation_running(philo->philo_data))
	{
		if (ft_eat(philo) == PHILO_DEATH)
			break ;
		if (!get_simulation_running(philo->philo_data))
		{
			sem_post(philo->philo_data->forks_sem);
			sem_post(philo->philo_data->forks_sem);
			break ;
		}
		if (ft_sleep(philo) == PHILO_DEATH)
			break ;
		if (!get_simulation_running(philo->philo_data))
			break ;
		if (ft_think(philo) == PHILO_DEATH)
			break ;
	}
	exit(0);
}

/* ************************************************************************** */
static int	ft_think(t_philo *philo)
{
	print_msg(philo->philo_data, philo->id, "is thinking");
	if (!get_simulation_running(philo->philo_data))
		return (PHILO_DEATH);
	return (SUCCESS);
}

/* ************************************************************************** */
static int	ft_sleep(t_philo *philo)
{
	print_msg(philo->philo_data, philo->id, "is sleeping");
	sem_post(philo->philo_data->forks_sem);
	sem_post(philo->philo_data->forks_sem);
	if (get_simulation_running(philo->philo_data))
		usleep(philo->philo_data->sleep_time * 1000);
	else
		return (PHILO_DEATH);
	return (SUCCESS);
}
