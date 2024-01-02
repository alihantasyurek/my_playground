#include "philo.h"

/*******************************************************/
/*******************************************************/
void	set_int(pthread_mutex_t	*mutex, int *dest, int value)
{
    pthread_mutex_lock(mutex);
	*dest = value;
    pthread_mutex_unlock(mutex);
}

/* can make both int and make it set_value | get value */
int     get_int(pthread_mutex_t	*mutex, int *value)
{
	int ret;

    pthread_mutex_lock(mutex);
    //reading thread safe
	ret = *value;
    pthread_mutex_unlock(mutex);
	return (ret);
}
//you're using it with get int don't forget that 
int simulation_finished(t_table *table)
{
    return (get_int(&table->table_mutex, &table->end_simulation));
}

/*******************************************************/
/*******************************************************/

void    wait_all_threads(t_table *table)
{
    while(get_int(&table->table_mutex, &table->all_threads_ready))
        ;

}

void    *dinner(void *data)
{
    t_philo *philo;
    philo = (t_philo *)data;

    wait_all_threads(philo->table);

    // set last meal time

    while (simulation_finished(philo->table)) // might be reversed.
    {
        // am i full
        if (philo->full) // TODO thread safe?
            break;
        //eat

        //sleep

        //thinking
    }

return NULL;
}

int    dinner_start(t_table *table)
{
    int i;

    i = -1;
    if (table->philo_nbr == 1)
    //TODO;
    while (++i < table->philo_nbr)
        if(pthread_create(&table->philos[i].thread_id,NULL,dinner,&table->philos[i]))
            return FAILURE;
//start_sim
table->start_simulation = gettime_ms();
    if(table->start_simulation == FAILURE)
           return FAILURE;

//now all the threads are ready!
set_int(&table->table_mutex,&table->all_threads_ready,SUCCESS);

//Wait for everyone to finish
i = -1;
while (++i < table->philo_nbr)
    if(pthread_join(table->philos[i].thread_id,NULL))
        return FAILURE;
// if we manage to reach here all philos are full!
return SUCCESS;
}