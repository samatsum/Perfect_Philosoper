/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:57:35 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/30 17:01:39 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	ft_atoi(char *str);

/* ************************************************************************** */
int	ft_atoi(char *str)
{
	int		count;
	long	result;
	int		sign;

	count = 0;
	result = 0;
	sign = 1;
	while (str[count] == '\r' || str[count] == '\t' || str[count] == ' '
		|| str[count] == '\f' || str[count] == '\v' || str[count] == '\n')
		count++;
	if (str[count] == '-')
	{
		sign = -1;
		count++;
	}
	else if (str[count] == '+')
		count++;
	if (!(str[count] >= '0' && str[count] <= '9'))
		return (0);
	while (str[count] >= '0' && str[count] <= '9')
		result = result * 10 + (str[count++] - '0');
	return (result * sign);
}
