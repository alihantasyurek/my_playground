#include "philo.h"
#include <sys/time.h> // be careful with these

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