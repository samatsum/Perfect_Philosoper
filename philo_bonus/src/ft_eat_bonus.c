/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 13:12:31 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/30 17:01:39 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int			ft_eat(t_philo *philo);
static int	handle_only1_philo(t_philo *philo);

/* ************************************************************************** */
/* ************************************************************************** */
int	ft_eat(t_philo *philo)
{
	t_data	*p_data = philo->philo_data;
	if (!get_simulation_running(p_data))
		return (PHILO_DEATH);
	if (p_data->nb_philos == 1)
		return (handle_only1_philo(philo));
	/* Take forks */
	sem_wait(p_data->forks_sem);
	print_msg(p_data, philo->id, "has taken a fork");
	sem_wait(p_data->forks_sem);
	print_msg(p_data, philo->id, "has taken a fork");
	/* Eat */
	print_msg(p_data, philo->id, "is eating");
	philo->last_eat_time = get_time();
	ft_usleep(p_data->eat_time);
	/* Increment meal count and signal if needed */
	philo->nb_meals_ate++;
	if (p_data->nb_must_meals > 0 && philo->nb_meals_ate == p_data->nb_must_meals)
		sem_post(p_data->meals_sem); /* Signal exactly once when threshold reached */
	return (SUCCESS);
}

/* ************************************************************************** */
static int	handle_only1_philo(t_philo *philo)
{
	t_data *p_data;
	p_data = philo->philo_data;
	/* Take the only fork */
	sem_wait(p_data->forks_sem);
	print_msg(p_data, philo->id, "has taken a fork");
	/* Wait until death */
	ft_usleep(p_data->die_time);
	/* Return fork */
	sem_post(p_data->forks_sem);
	return (PHILO_DEATH);
}
