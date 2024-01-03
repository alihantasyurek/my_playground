#include "philo.h"

// check if last_meal time > last meal they die
int philo_died(t_philo *philo)
{
                                    //it's gonna return 0 when it's full 
    if (get_int(&philo->philo_mutex,!(&philo->full))) // maybe philo is full we need to check that 
        return FAILURE;

    long    elapsed;
    long    t_to_die;

    elapsed = gettime_ms() - get_long(&philo->philo_mutex, &philo->last_meal_time);
t_to_die = philo->table->time_to_die / 1e3; // to convert to ms/ miliseconds;
if (elapsed > t_to_die)
        return SUCCESS;
return FAILURE;
}

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
int     i;
t_table *table;

table = (t_table *)data;

// make sure all philo running
// apinloxk till all threads run
while (all_threads_running(&table->table_mutex, &table->threads_running_nbr, table->philo_nbr)) // might be reversed
                    ;
while(simulation_finished(table))// might be reversed
{
    i = -1;
    while(++i < table->philo_nbr && simulation_finished(table))
    {
        if(philo_died(table->philos + i)) // TODO
        {
            set_int(&table->table_mutex,&table->end_simulation, SUCCESS);
            print_status(DIED, table->philos + i, DEBUG_MODE); // remove the debug mode;
        }
    }
}

return (NULL);
}

//1:41:51