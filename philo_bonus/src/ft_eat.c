/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 13:12:31 by samatsum          #+#    #+#             */
/*   Updated: 2025/01/19 14:48:30 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int			ft_eat(t_philo *philo);
static int	take_forks(t_philo *philo);
static int	take_left_fork(t_philo *philo);
static int	take_right_fork(t_philo *philo);
static int	handle_only1_philo(t_philo *philo);

/* ************************************************************************** */
int	ft_eat(t_philo *philo)
{
	if (take_forks(philo) == PHILO_DEATH)
		return (PHILO_DEATH);
	set_philo_status(philo, EATING);
	print_msg(philo->data, philo->id, "is eating");
	philo->last_eat_time = get_time();
	ft_usleep(philo->data->eat_time);
	philo->nb_meals_ate++;
	return (SUCCESS);
}

/* ************************************************************************** */
static int	take_forks(t_philo *philo)
{
	if ((philo->data->nb_philos) == 1)
		return (handle_only1_philo(philo));
	if (take_right_fork(philo) == PHILO_DEATH)
		return (PHILO_DEATH);
	if (take_left_fork(philo) == PHILO_DEATH)
	{
		pthread_mutex_unlock(philo->right_f);
		return (PHILO_DEATH);
	}
	return (SUCCESS);
}

/* ************************************************************************** */
static int	take_left_fork(t_philo *philo)
{
	if (time_over(philo) || philo->status == DEAD)
		return (PHILO_DEATH);
	pthread_mutex_lock(philo->left_f);
	print_msg(philo->data, philo->id, "has taken a fork");
	return (SUCCESS);
}

/* ************************************************************************** */
static int	take_right_fork(t_philo *philo)
{
	if (time_over(philo) || philo->status == DEAD)
		return (PHILO_DEATH);
	pthread_mutex_lock(philo->right_f);
	print_msg(philo->data, philo->id, "has taken a fork");
	return (SUCCESS);
}

/* ************************************************************************** */
static int	handle_only1_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_f);
	print_msg(philo->data, philo->id, "has taken a fork");
	ft_usleep(philo->data->die_time);
	pthread_mutex_unlock(philo->left_f);
	set_philo_status(philo, DEAD);
	return (PHILO_DEATH);
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