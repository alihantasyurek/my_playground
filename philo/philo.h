#ifndef PHILO_H
# define PHILO_H

// if one or more files uses same header files you can add it here
// else if one file uses one function from header don't add it here
#define SUCCESS 0
#define FAILURE -1 

#    include <stdbool.h>//remove this it is only for debug mode
# ifndef DEBUG_MODE
#  define DEBUG_MODE 1 // delete before push it and fix the print stuff
# endif

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}			t_philo_status;

typedef struct s_fork
{
    pthread_mutex_t fork;
    int             fork_id; // which fork philo has taken
}t_fork;


typedef struct s_philo
{
    int             id;
    long            meals_counter;
    int             full;
    long            last_meal_time;
    t_fork          *first_fork;
    t_fork          *second_fork;
    pthread_t       thread_id; // a philo is a thread
    pthread_mutex_t philo_mutex; // useful for races wqith the monitor
    struct s_table  *table;
}t_philo;

typedef struct s_table
{
    long    philo_nbr;
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;
    long    nbr_limit_meals; // if -1 it's a flag,when given it's a value
    long    start_simulation; // time stamps starting from this value;
    int     end_simulation;  // To turn it off > when philo dies | meals satisfied
    int     all_threads_ready; // sync philos
    pthread_mutex_t table_mutex; // avoid races while reading from table
    pthread_mutex_t print_mutex;
    t_fork  *forks; // array to forks 
    t_philo *philos; // array for philos
    pthread_t   monitor;
    long    threads_running_nbr;
    
}t_table;

int     digit_control(char **argv);
int     check_input(int argc,char **argv);
int     input_value(int argc,char **argv);
long    ft_atol(const char *str);
void    format_error(void);
void    parse_input(t_table *table,char **argv);
int     data_init(t_table *table);
void    philo_init(t_table *table);
void    assign_forks(t_philo *philo, t_fork *forks, int philo_index_pos);
int     dinner_start(t_table *table);
void    *dinner(void *data);
void    wait_all_threads(t_table *table);
void	set_int(pthread_mutex_t	*mutex, int *dest, int value);
int     get_int(pthread_mutex_t	*mutex, int *value);
long    gettime_ms(void);
void    precise_usleep(long usec, t_table *table);
void    print_status(t_philo_status status, t_philo *philo, bool debug); // remove the bool part
int     simulation_finished(t_table *table);
void	set_int(pthread_mutex_t	*mutex, int *dest, int value);
void    set_long(pthread_mutex_t	*mutex, long *dest, long value);
int     get_int(pthread_mutex_t	*mutex, int *value);
long    get_long(pthread_mutex_t	*mutex, long *value);
void    *monitor_dinner(void *data);
int     all_threads_running(pthread_mutex_t *mutex, long *threads, long philo_nbr);
void    increase_long(pthread_mutex_t *mutex, long *value);

#endif