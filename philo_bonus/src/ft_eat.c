/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 13:12:31 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/30 03:40:40 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int			ft_eat(t_philo *philo);
static int	handle_only1_philo(t_philo *philo);

/* ************************************************************************** */
int	ft_eat(t_philo *philo)
{
	t_data *data;
	
	data = philo->data;
	
	if (data->nb_philos == 1)
		return (handle_only1_philo(philo));
	
	/* 一つ目のフォークを取る */
	sem_wait(data->forks_sem);
	print_msg(data, philo->id, "has taken a fork");
	
	/* 二つ目のフォークを取る */
	sem_wait(data->forks_sem);
	print_msg(data, philo->id, "has taken a fork");
	
	/* 食事開始 */
	print_msg(data, philo->id, "is eating");
	philo->last_eat_time = get_time();
	ft_usleep(data->eat_time);
	
	/* 食事回数をカウント */
	philo->nb_meals_ate++;
	
	/* すべての食事を完了した場合、通知 */
	if (data->nb_must_meals > 0 && philo->nb_meals_ate == data->nb_must_meals)
		sem_post(data->meals_sem);
	
	/* フォークを戻す */
	sem_post(data->forks_sem);
	sem_post(data->forks_sem);
	
	return (SUCCESS);
}

/* ************************************************************************** */
static int	handle_only1_philo(t_philo *philo)
{
	t_data *data;
	
	data = philo->data;
	
	/* フォークを一つだけ取得 */
	sem_wait(data->forks_sem);
	print_msg(data, philo->id, "has taken a fork");
	
	/* 死亡時間待機 */
	ft_usleep(data->die_time);
	
	/* フォークを戻す */
	sem_post(data->forks_sem);
	
	return (PHILO_DEATH);
}
