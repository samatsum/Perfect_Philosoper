/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 13:12:31 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/30 12:58:48 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int			ft_eat(t_philo *philo);
static int	handle_only1_philo(t_philo *philo);

/* ************************************************************************** */
/* ************************************************************************** */
int	ft_eat(t_philo *philo)
{
	t_data *data = philo->data;
	
	if (!get_simulation_running(data))
		return (PHILO_DEATH);
		
	if (data->nb_philos == 1)
		return (handle_only1_philo(philo));
	
	/* Take forks */
	sem_wait(data->forks_sem);
	print_msg(data, philo->id, "has taken a fork");
	sem_wait(data->forks_sem);
	print_msg(data, philo->id, "has taken a fork");
	
	/* Eat */
	print_msg(data, philo->id, "is eating");
	philo->last_eat_time = get_time();
	ft_usleep(data->eat_time);
	
	/* Increment meal count and signal if needed */
	philo->nb_meals_ate++;
	if (data->nb_must_meals > 0 && philo->nb_meals_ate == data->nb_must_meals)
		sem_post(data->meals_sem); /* Signal exactly once when threshold reached */
	return (SUCCESS);
}

/* ************************************************************************** */
static int	handle_only1_philo(t_philo *philo)
{
	t_data *data;
	data = philo->data;
	/* Take the only fork */
	sem_wait(data->forks_sem);
	print_msg(data, philo->id, "has taken a fork");
	/* Wait until death */
	ft_usleep(data->die_time);
	/* Return fork */
	sem_post(data->forks_sem);
	return (PHILO_DEATH);
}
