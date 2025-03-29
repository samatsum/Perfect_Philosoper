/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 21:33:22 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/30 01:25:15 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int			main(int argc, char **argv);
static int	philosophers(int argc, char **argv);
static void	print_instruction(void);
static int	monitor_meals(t_data *data);

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
	t_data	data;

	if (init_data(&data, argc, argv) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	
	if (init_semaphores(&data) == FAIL)
	{
		free_data(&data);
		return (FAIL);
	}
	
	init_philos(&data);
	
	if (run_processes(&data) == FAIL)
	{
		cleanup_semaphores(&data);
		free_data(&data);
		return (FAIL);
	}
	
	/* 親プロセスで食事完了監視を行う */
	if (data.nb_must_meals > 0)
		monitor_meals(&data);
	
	/* 全プロセスの終了を待つ */
	wait_processes(&data);
	
	/* 後片付け */
	cleanup_semaphores(&data);
	free_data(&data);
	
	return (ALL_OK);
}

/* ************************************************************************** */
static int	monitor_meals(t_data *data)
{
	int	i;
	
	/* 各哲学者からの食事完了通知を待つ */
	for (i = 0; i < data->nb_philos; i++)
		sem_wait(data->meals_sem);
	
	/* すべての哲学者が食事を完了 - シミュレーション終了 */
	for (i = 0; i < data->nb_philos; i++)
		kill(data->philo_pids[i], SIGTERM);
	
	/* 監視プロセスも終了 */
	kill(data->monitor_pid, SIGTERM);
	
	return (SUCCESS);
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
