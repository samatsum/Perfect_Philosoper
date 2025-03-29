/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 09:14:32 by samatsum          #+#    #+#             */
/*   Updated: 2025/01/19 14:04:03 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int			check_input(int argc, char **argv);
static int	wrong_input_check(int argc, char **argv);
static int	is_input_digit(int argc, char **argv);

/* ************************************************************************** */
int	check_input(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (WRONG_INPUT);
	if (is_input_digit(argc, argv) == WRONG_INPUT)
		return (WRONG_INPUT);
	if (wrong_input_check(argc, argv) == WRONG_INPUT)
		return (WRONG_INPUT);
	return (INPUT_OK);
}

/* ************************************************************************** */
static int	wrong_input_check(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc == 6 && ft_atoi(argv[5]) <= 0)
		return (WRONG_INPUT);
	if (ft_atoi(argv[i]) < 1)
		return (WRONG_INPUT);
	while (++i < 5)
	{
		if (ft_atoi(argv[i]) <= 10)
			return (WRONG_INPUT);
	}
	return (INPUT_OK);
}

/* ************************************************************************** */
static int	is_input_digit(int argc, char **argv)
{
	int	i;
	int	k;

	i = 1;
	while (i < argc)
	{
		k = 0;
		while (argv[i][k] != '\0')
		{
			if (argv[i][k] < '0' || argv[i][k] > '9')
				return (WRONG_INPUT);
			k++;
		}
		i++;
	}
	return (INPUT_OK);
}
