#include "philo.h"
#include <sys/time.h> // be careful with these
#include <unistd.h> // usleep

/*******************************************************/
/*******************************************************/
void	set_int(pthread_mutex_t	*mutex, int *dest, int value)
{
    if(pthread_mutex_lock(mutex))
        return ;
	*dest = value;
    if(pthread_mutex_unlock(mutex))
        return ;
}

void     set_long(pthread_mutex_t	*mutex, long *dest, long value)
{
    if(pthread_mutex_lock(mutex))
        return ;
	*dest = value;
    if(pthread_mutex_unlock(mutex))
        return ;
}

/* can make both int and make it set_value | get value */
int     get_int(pthread_mutex_t	*mutex, int *value)
{
	int ret;

    if(pthread_mutex_lock(mutex))
        return FAILURE;
    //reading thread safe
	ret = *value;
    if(pthread_mutex_unlock(mutex))
        return FAILURE;
	return (ret);
}

long     get_long(pthread_mutex_t	*mutex, long *value)
{
	long ret;

    if(pthread_mutex_lock(mutex))
        return FAILURE;
    //reading thread safe
	ret = *value;
    if(pthread_mutex_unlock(mutex))
        return FAILURE;
	return (ret);
}


//you're using it with get int don't forget that 
int simulation_finished(t_table *table)
{
    return (get_int(&table->table_mutex, &table->end_simulation));
}

/*******************************************************/
/*******************************************************/

long    gettime_ms(void)
{
    struct timeval  tv;

    if(gettimeofday(&tv,NULL))
        return FAILURE;
return (tv.tv_sec * 1e3) + (tv.tv_usec / 1e3);
}

// getting table to check if the simulation is finished 
void    precise_usleep(long usec, t_table *table)
{
    long     start;
    long     elapsed;
    long     remain;
    start = gettime_ms();
    while(gettime_ms() - start < usec) // Repeat the loop till start exceeds usec
    {
    if (!simulation_finished(table)) // simulation finished will return 0 on success==
        break;                       // might be reversed logic
    elapsed = gettime_ms() - start; // Calculates the time elapsed since the start time.
    remain = usec - elapsed; // achieve the desired delay?
    // to get a spinlock threshold
    if (remain > 1e3)
        usleep(remain / 2);
    else 
        while (gettime_ms() - start < usec)
                    ;
    }
}