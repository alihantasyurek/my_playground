#ifndef PHILO_H
# define PHILO_H

// if one or more files uses same header files you can add it here
// else if one file uses one function from header don't add it here
#include <pthread.h>
#include <stdlib.h>
#define SUCCESS 0
#define FAILURE -1 

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
    int             is_full;
    long            last_meal_time;
    t_fork          *left_fork;
    t_fork          *right_fork;
    pthread_t       thread_id; // a philo is a thread
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

#endif