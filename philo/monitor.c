#include "philo.h"

/*
 * Monitor waits all threads are running the 
 * simulation before searching deaths
*/
int all_threads_running(pthread_mutex_t *mutex, long *threads,
		long philo_nbr)
{
	bool	ret;

	ret = false;

 if(pthread_mutex_lock(mutex))
    return false;

	if (*threads == philo_nbr)
		ret = true;

 if(pthread_mutex_unlock(mutex))
    return false;

return (ret);
}

/*
 * 1) Check if the philo is full,
 * 	he has already finished
 * 	his own simulation. Monitor 
 * 	does not care. Return.
 *
 * 2) Check if the philo is died
 * reading in a thread safe manner
 * the last_meal 
 *
 * 🚨 time_to_die / 1e3 🚨
 * I need to convert back from micro to milli
 * t_to_die
*/
int philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_int(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = gettime_ms() - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	t_to_die = philo->table->time_to_die;
	if (elapsed > t_to_die)
		return (true);
	return (false);
}

/*
 * THREAD continuosly monitoring death philos
 * Two conditions to finish
 *
 * 1) if philo is death, set the flag end simulation to true and return
 * 2) All philos are full, end_simulation will be turned on by the main
 * 		thread in this case, when all the philos are JOINED
 * 	💡end_simulation is changed by the main thread | monitor💡
*/
void	*monitor_dinner(void *data)
{
	int			i;
	t_table		*table;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex,
			&table->threads_running_nbr, table->philo_nbr))
		;
	while (!simulation_finished(table))
	{	
		i = -1;
		while (++i < table->philo_nbr && !simulation_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				set_int(&table->table_mutex, &table->end_simulation, true);
				print_status(DIED, table->philos + i, DEBUG_MODE);
			}
		}
	}
	return (NULL);
}