#include "philo.h"


// time_ms philo_id action
void    print_status(t_philo_status status, t_philo *philo, int debug)// delete debug
{
    pthread_mutex_lock(philo->table->print_mutex);

    pthread_mutex_unlock(philo->table->print_mutex);
}