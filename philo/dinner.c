#include "philo.h"

/*
    eat routine
    1) grab the forks: here first & second fork is handy 
    i don't wotty about left or right
    2) eat : write eat, update last meal, update meals counter,
        eventually bool full
    3) release the forks
*/

void thinking(t_philo *philo)
{
    print_status(THINKING, philo, DEBUG_MODE); // rmv debug mode
}

void eat(t_philo *philo)
{
    if(pthread_mutex_lock(&philo->first_fork->fork))
        return ;
    print_status(TAKE_FIRST_FORK,philo,DEBUG_MODE); // delete debug mode

    if(pthread_mutex_lock(&philo->second_fork->fork))
        return ;
    print_status(TAKE_SECOND_FORK,philo,DEBUG_MODE); // delete debug mode

    // set last meal time 
    //this is also gonna get read by the monitor thread 
    //every philo is a mutex this will be used with the monitor
    set_long(&philo->philo_mutex, &philo->last_meal_time, gettime_ms());
    philo->meals_counter++;
    print_status(EATING, philo, DEBUG_MODE); //rmv debug mode
    precise_usleep(philo->table->time_to_eat, philo->table);
    if (philo->table->nbr_limit_meals > 0 
    && philo->meals_counter == philo->table->nbr_limit_meals)
    set_int(&philo->philo_mutex, &philo->full, SUCCESS);

    if(pthread_mutex_unlock(&philo->first_fork->fork))
        return ;
    if(pthread_mutex_unlock(&philo->second_fork->fork))
        return ;
}

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
        // if (philo->full) // TODO thread safe?
        //     break;
        //eat
        eat(philo);

        //sleep
        print_status(SLEEPING,philo,DEBUG_MODE); // delete this debug mode before push
        precise_usleep(philo->table->time_to_sleep, philo->table);

        //thinking
        thinking(philo);
    }

return NULL;
}

int    dinner_start(t_table *table)
{
    int i;

i = -1;
//if (table->philo_nbr == 1)
// TODO MUST!!!!!!!!!!!!!!
//

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