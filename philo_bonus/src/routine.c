/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 21:09:44 by samatsum          #+#    #+#             */
/*   Updated: 2025/01/19 14:48:33 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void		*routine(void *philo_p);
void		*special_routine(void *philo_p);
static void	routine_while(t_philo	*philo);
static int	ft_think(t_philo *philo);
static int	ft_sleep(t_philo *philo);

/* ************************************************************************** */
void	*routine(void *philo_p)
{
	t_philo	*philo;

	philo = (t_philo *) philo_p;
	while (philo->data->simulation_start_time == 0)
		usleep(10);
	philo->last_eat_time = philo->data->simulation_start_time;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->eat_time);
	routine_while(philo);
	return (NULL);
}

/* ************************************************************************** */
void	*special_routine(void *philo_p)
{
	t_philo	*philo;

	philo = (t_philo *) philo_p;
	while (philo->data->simulation_start_time == 0)
		usleep(10);
	philo->last_eat_time = philo->data->simulation_start_time;
	ft_usleep(philo->usleep_time);
	routine_while(philo);
	return (NULL);
}

/* ************************************************************************** */
static void	routine_while(t_philo	*philo)
{
	while (philo->status != DEAD)
	{
		if (ft_eat(philo) == PHILO_DEATH)
			break ;
		if (philo->status == DEAD)
		{
			pthread_mutex_unlock(philo->left_f);
			pthread_mutex_unlock(philo->right_f);
			break ;
		}
		if (ft_sleep(philo) == PHILO_DEATH)
			break ;
		if (philo->status == DEAD)
			break ;
		if (ft_think(philo) == PHILO_DEATH)
			break ;
	}
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
	{
		pthread_mutex_unlock(philo->left_f);
		pthread_mutex_unlock(philo->right_f);
		return (PHILO_DEATH);
	}
	print_msg(philo->data, philo->id, "is sleeping");
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_unlock(philo->right_f);
	if (philo->status == DEAD)
		return (PHILO_DEATH);
	ft_usleep(philo->data->sleep_time);
	return (SUCCESS);
}
