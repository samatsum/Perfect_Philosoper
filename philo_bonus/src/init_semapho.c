
#include "../include/philo.h"

int init_semaphores(t_data *data)
{
    // 既存のセマフォを削除（前回の実行で残っている可能性がある）
    sem_unlink("/philo_forks");
    sem_unlink("/philo_print");
    sem_unlink("/philo_dead");
    sem_unlink("/philo_meals");
    sem_unlink("/philo_data");
    
    // セマフォの作成
    data->forks_sem = sem_open("/philo_forks", O_CREAT | O_EXCL, 0644, data->nb_philos);
    data->print_sem = sem_open("/philo_print", O_CREAT | O_EXCL, 0644, 1);
    data->dead_sem = sem_open("/philo_dead", O_CREAT | O_EXCL, 0644, 0);
    data->meals_sem = sem_open("/philo_meals", O_CREAT | O_EXCL, 0644, 0);
    data->data_sem = sem_open("/philo_data", O_CREAT | O_EXCL, 0644, 1);
    
    if (data->forks_sem == SEM_FAILED || data->print_sem == SEM_FAILED ||
        data->dead_sem == SEM_FAILED || data->meals_sem == SEM_FAILED ||
        data->data_sem == SEM_FAILED)
        return (FAIL);
        
    return (SUCCESS);
}

void cleanup_semaphores(t_data *data)
{
    // セマフォのクローズ
    sem_close(data->forks_sem);
    sem_close(data->print_sem);
    sem_close(data->dead_sem);
    sem_close(data->meals_sem);
    sem_close(data->data_sem);
    
    // セマフォの削除
    sem_unlink("/philo_forks");
    sem_unlink("/philo_print");
    sem_unlink("/philo_dead");
    sem_unlink("/philo_meals");
    sem_unlink("/philo_data");
}