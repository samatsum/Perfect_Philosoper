/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 21:33:22 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/30 19:14:53 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int			main(int argc, char **argv);
static int	philosophers(int argc, char **argv);
static void	print_instruction(void);

int	main(int argc, char **argv)
{
	if (check_input(argc, argv) == WRONG_INPUT)
	{
		print_instruction();
		return (WRONG_INPUT);
	}
	if (philosophers(argc, argv) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	return (ALL_OK);
}

/* ************************************************************************** */
static int	philosophers(int argc, char **argv)
{
	t_data	main_data;

	if (init_data(&main_data, argc, argv) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (init_semaphores(&main_data) == FAIL)
	{
		free_data(&main_data);
		return (FAIL);
	}
	init_philos(&main_data);
	if (run_processes(&main_data) == FAIL)
	{
		cleanup_semaphores(&main_data);
		free_data(&main_data);
		return (FAIL);
	}
	/* Create monitor processes */
	if (create_monitor_processes(&main_data) == FAIL)
	{
		for (int i = 0; i < main_data.nb_philos; i++)
			kill(main_data.philo_pids[i], SIGTERM);
		cleanup_semaphores(&main_data);
		free_data(&main_data);
		return (FAIL);
	}
	/* Wait for processes to complete */
	wait_processes(&main_data);
	/* Cleanup */
	cleanup_semaphores(&main_data);
	free_data(&main_data);
	return (0);
}
/* ************************************************************************** */
static void	print_instruction(void)
{
	printf("\t\tWRONG INPUT!\n\n");
	printf("./philo nb_philos time_to_die ");
	printf("time_to_eat time_to_sleep ");
	printf("number_of_times_each_philosopher_must_eat (optional argument)\n");
	printf("Example:\n\n");
	printf("./philo 4 800 200 200 5\n\n");
	printf("nb_philos: +1~\n");
	printf("time_to_die: +11~\n");
	printf("time_to_eat: +11~\n");
	printf("time_to_sleep: +11~\n");
	printf("number_of_times_each_philosopher_must_eat: +1~");
	printf("\n");
}
