/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 13:12:31 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/29 23:11:49 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int			ft_eat(t_philo *philo);
static int	take_forks(t_philo *philo);

/* ************************************************************************** */
int	ft_eat(t_philo *philo)
{
	if (take_forks(philo) == PHILO_DEATH)
		return (PHILO_DEATH);
		
	set_philo_status(philo, EATING);
	print_msg(philo->data, philo->id, "is eating");
	
	// Update last eat time and start eating
	philo->last_eat_time = get_time();
	ft_usleep(philo->data->eat_time);
	
	// Increment meal count and check if philosopher is full
	philo->nb_meals_ate++;
	if (philo->data->nb_must_meals > 0 && 
		philo->nb_meals_ate >= philo->data->nb_must_meals)
	{
		// Signal that this philosopher has eaten enough
		sem_post(philo->data->meals_sem);
	}
	
	// Release the forks
	sem_post(philo->data->forks_sem);
	sem_post(philo->data->forks_sem);
	
	return (SUCCESS);
}

/* ************************************************************************** */
static int	take_forks(t_philo *philo)
{
	// Take first fork
	sem_wait(philo->data->forks_sem);
	print_msg(philo->data, philo->id, "has taken a fork");
	
	// If there's only one philosopher, wait until death
	if (philo->data->nb_philos == 1)
	{
		ft_usleep(philo->data->die_time);
		sem_post(philo->data->forks_sem); // Release the fork
		set_philo_status(philo, DEAD);
		return (PHILO_DEATH);
	}
	
	// Take second fork
	sem_wait(philo->data->forks_sem);
	print_msg(philo->data, philo->id, "has taken a fork");
	
	return (SUCCESS);
}

// void	print_leftmsg(t_data *data, int id, char *msg)
// {
// 	int	time;

// 	pthread_mutex_lock(&data->mutex_print);
// 	time = get_time() - data->simulation_start_time;
// 	if (get_keep_iterating_flag(data))
// 		printf("%lu %d %s (%d fork)\n", time, id, msg, id);
// 	pthread_mutex_unlock(&data->mutex_print);
// }

// void	print_rightmsg(t_data *data, int id, char *msg)
// {
// 	int	time;
// 	int		k;

// 	k = id - 1;
// 	if(k == 0)
// 		k = data->nb_philos;

// 	pthread_mutex_lock(&data->mutex_print);
// 	time = get_time() - data->simulation_start_time;
// 	if (get_keep_iterating_flag(data))
// 		printf("%lu %d %s (%d fork)\n", time, id, msg, k);
// 	pthread_mutex_unlock(&data->mutex_print);
// }