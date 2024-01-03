#include "philo.h"

// monitor busy waits until all threads running
int all_threads_running(pthread_mutex_t *mutex, long *threads,
        long philo_nbr)
{
    int     ret;

    ret = FAILURE;
    pthread_mutex_lock(mutex);
    if (*threads == philo_nbr)
        ret = SUCCESS;
    pthread_mutex_unlock(mutex);

return (ret);
}

void    *monitor_dinner(void *data)
{
t_table *table;

table = (t_table *)data;

// make sure all philo running
// apinloxk till all threads run
while (all_threads_running(&table->table_mutex, &table->threads_running_nbr, table->philo_nbr)) // might be reversed
                    ;

return (NULL);
}