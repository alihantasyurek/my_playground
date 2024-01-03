#include "philo.h"


# define RST    "\033[0m"      /* Reset to default color */
# define RED	"\033[1;31m"   /* Bold Red */
# define G      "\033[1;32m"   /* Bold Green */
# define Y      "\033[1;33m"   /* Bold Yellow */
# define B      "\033[1;34m"   /* Bold Blue */
# define M      "\033[1;35m"   /* Bold Magenta */
# define C      "\033[1;36m"   /* Bold Cyan */
# define W      "\033[1;37m"   /* Bold White */

static void	write_status_debug(t_philo_status status, t_philo *philo,
		long elapsed)
{
	if (TAKE_FIRST_FORK == status && simulation_finished(philo->table))
		printf(W"%6ld"RST" %d has taken the 1° fork 🍽"
			"\t\t\tn°"B"[🍴 %d 🍴]\n"RST, elapsed, philo->id,
			philo->first_fork->fork_id);
	else if (TAKE_SECOND_FORK == status && simulation_finished(philo->table))
		printf(W"%6ld"RST" %d has taken the 2° fork 🍽"
			"\t\t\tn°"B"[🍴 %d 🍴]\n"RST, elapsed, philo->id,
			philo->second_fork->fork_id);
	else if (EATING == status && simulation_finished(philo->table))
		printf(W"%6ld"C" %d is eating 🍝"
			"\t\t\t"Y"[🍝 %ld 🍝]\n"RST, elapsed, philo->id, philo->meals_counter);
	else if (SLEEPING == status && simulation_finished(philo->table))
		printf(W"%6ld"RST" %d is sleeping 😴\n", elapsed, philo->id);
	else if (THINKING == status && simulation_finished(philo->table))
		printf(W"%6ld"RST" %d is thinking 🤔\n", elapsed, philo->id);
	else if (DIED == status)
		printf(RED"\t\t💀💀💀 %6ld %d died   💀💀💀\n"RST, elapsed, philo->id);
}

// time_ms philo_id action
void    print_status(t_philo_status status, t_philo *philo, bool debug)// delete debug after 
{
    long elapsed; 

    elapsed = gettime_ms() - philo->table->start_simulation;
    /*
    if (philo->full) // needs to be thread safe will do this after we create the monitor
        return;
    */

if(pthread_mutex_lock(&philo->table->print_mutex))
	return ;

    if(debug)   // get rid of the debug before pushing it's just for test
        write_status_debug(status, philo, elapsed);
    else{
        if((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status) && simulation_finished(philo->table))
            printf("%ld %d has taken a fork\n", elapsed, philo->id);
        else if (EATING == status && simulation_finished(philo->table))
			printf("%ld %d is eating\n", elapsed, philo->id);
		else if (SLEEPING == status && simulation_finished(philo->table))
			printf("%ld %d is sleeping\n", elapsed, philo->id);
		else if (THINKING == status && simulation_finished(philo->table))
			printf("%ld %d is thinking\n", elapsed, philo->id);
		else if (DIED == status)
			printf("%ld %d is died\n", elapsed, philo->id);
	}

if(pthread_mutex_unlock(&philo->table->print_mutex))
	return ;
}


