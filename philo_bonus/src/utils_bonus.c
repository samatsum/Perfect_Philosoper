/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 11:46:56 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/29 23:13:33 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	free_data(t_data *data);
void	print_msg(t_data *data, int id, char *msg);
void	set_philo_status(t_philo *philo, enum e_status status);
void	close_semaphores(t_data *data);
char	*ft_itoa(int n);

/* ************************************************************************** */
void	free_data(t_data *data)
{
	int	i;
	
	if (data->philos)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			if (data->philos[i].philo_dead_sem != SEM_FAILED)
				sem_close(data->philos[i].philo_dead_sem);
			sem_unlink(data->philos[i].philo_dead_sem_name);
			i++;
		}
		free(data->philos);
	}
}

/* ************************************************************************** */
void	print_msg(t_data *data, int id, char *msg)
{
	size_t	time;

	sem_wait(data->print_sem);
	time = get_time() - data->simulation_start_time;
	printf("%lu %d %s\n", time, id, msg);
	sem_post(data->print_sem);
}

/* ************************************************************************** */
void	set_philo_status(t_philo *philo, enum e_status new_status)
{
	if (philo->status != DEAD)
		philo->status = new_status;
}

/* ************************************************************************** */
void	close_semaphores(t_data *data)
{
	if (data->forks_sem != SEM_FAILED)
		sem_close(data->forks_sem);
	if (data->print_sem != SEM_FAILED)
		sem_close(data->print_sem);
	if (data->dead_sem != SEM_FAILED)
		sem_close(data->dead_sem);
	if (data->meals_sem != SEM_FAILED)
		sem_close(data->meals_sem);
	
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_MEALS);
}

/* ************************************************************************** */
// Helper string functions needed for semaphore naming
void	ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void	ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
}

/* ************************************************************************** */
// Convert integer to string for semaphore names
static int	get_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	num;

	len = get_len(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		num = (long)n * -1;
	}
	else
		num = n;
	while (num)
	{
		str[--len] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}