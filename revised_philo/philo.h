#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> // maybe do these libraries to only one file
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

/*
 * While compiling use this
 * variable to see a better output
 * to debug
*/

# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

/*
 * PHILO MAX
 * by default 200
*/
#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define FAILURE -1
# ifndef PHILO_MAX
#  define PHILO_MAX 200 
# endif

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}			t_philo_status;

/**
 * Represents different units of time for use with a gettime function,
 * which can be used to get the current time or measure durations in
 * various units.
*/
typedef enum e_time_code
{
	SECONDS,
	MILLISECOND,
	MICROSECOND,
}		t_time_code;

/*
 * ENUM to handle all the mutex & thread functions
 * with a clean API interface
*/
typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}			t_opcode;

/*
** ANSI Escape Sequences for Bold Text Colors
** Usage: 
**     printf(R "This is red text." RST);
**     printf(B "This is blue text." RST);
** Remember to use RST to reset the color after setting it.
*/

# define RST    "\033[0m"      /* Reset to default color */
# define RED	"\033[1;31m"   /* Bold Red */
# define G      "\033[1;32m"   /* Bold Green */
# define Y      "\033[1;33m"   /* Bold Yellow */
# define B      "\033[1;34m"   /* Bold Blue */
# define M      "\033[1;35m"   /* Bold Magenta */
# define C      "\033[1;36m"   /* Bold Cyan */
# define W      "\033[1;37m"   /* Bold White */

//*******************************    STRUCTS    *******************************

/*
 * I have to declare t_table here because it's used
 * in philo before it is implemented
 * Typedef mutex, way to long pthread_mutex_t
*/
typedef struct s_table	t_table;

/*
 * FORK
 * I make it as a struct, id useful for debugging
*/
typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}				t_fork;

/*
** Struct s_philo - Represents a philosopher in the dining philosophers problem.
**
** Members:
** - id:            	Unique identifier for the philosopher.
** - full:          	Is philosopher full flag, when strict meals nbr.
** - meals_counter: 	Number of meals the philosopher has eaten.
** - last_meal_time: 	Time of the philosopher's last meal.
** - thread_id:     	Thread ID for the philosopher's thread.
** - first_fork:    	Pointer to the philosopher's first fork to take.
** - second_fork:   	Pointer to the philosopher's secon fork.
** - philo_data_mutex: 	Mutex for managing data races (access philo data
							concurrently) with the monitor thread)
** - table:		    	Pointer to table data, every philo can access
							all the "global data" in tabl in table.
*/
typedef struct s_philo
{
	int				id;
	int				full;
	long			meals_counter;
	long			last_meal_time;
	pthread_t		thread_id;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_mutex_t	philo_mutex;
	t_table			*table;
}				t_philo;

/*
** Struct: s_table
** The table holds information about the time constraints for the philosophers,
** whether there's a meal limit, the number of meals limit if applicable,
** the total number of philosophers, the starting time of the simulation,
** a fairness performance array to track the fairness of resource
** allocation among philosophers (at the end they ate ~equal meals), a thread
** for monitoring the philosophers, an array of forks, an array of philosophers,
** and a mutex for managing data races when writing to shared resources (stdout).
**
** Members:
** - time_to_die: Time after which a philosopher will die if they haven't eaten.
** - time_to_eat: Time it takes for a philosopher to eat a meal.
** - time_to_sleep: Time it takes for a philosopher to sleep.
** - nbr_limit_meals: The number of meals limit, if < 0 no limits.
** - philo_nbr: Total number of philosophers at the table.
** - start_simulation: The starting time of the simulation.
** - end_simulation: when a philo die, this flag ON
** - all_threads_ready: synchro the start of simulation
							monitor-philos.
** - threads_running_nbr: Helps me synchro the monitor thread
** - monitor: Thread for monitoring the philosophers.
** - forks: Pointer to an array of forks.
** - philosophers: Pointer to an array of philosophers.
** - table_mutex: Useful to manage data races monitor-philos
** - write_mutex: Mutex for managing data races when writing to stdout.
*/
struct	s_table
{
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_limit_meals;
	long				philo_nbr;
	long				start_simulation;
	int					end_simulation;
	int					all_threads_ready;
	long				threads_running_nbr;
	pthread_t			monitor;
	t_fork				*forks;
	t_philo				*philos;
	pthread_mutex_t		table_mutex;
	pthread_mutex_t		write_mutex;
};

//***************    PROTOTYPES     ***************
//******************************
//******************************
int		check_input(int argc,char **argv);
void	format_error(void);
int		input_value(int argc,char **argv);
long	ft_atol(const char *str);
int		digit_control(char **argv);
int 	data_init(t_table *table);
void	format_input(t_table *table, char **argv);
//******************************
//******************************

//*** functions with embedded controls to make the code DRY ***
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
			void *data, t_opcode opcode);
void	safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode);

//*** init table and philos data ***

//*** function to kick in the dinner ***
void	dinner_start(t_table *table);

//*** setter and getters, very useful to write DRY code ***
void	set_int(pthread_mutex_t *mutex, int *dest, int value);
int		get_int(pthread_mutex_t *mutex, int *value);
long	get_long(pthread_mutex_t *mutex, long *value);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
int		simulation_finished(t_table *table);

//*** utils ***
time_t	gettime(int time_code);
void	precise_usleep(long usec, t_table *table);
void	clean(t_table *table);
void	error_exit(const char *error);

//*** write the philo status ***
void	write_status(t_philo_status status, t_philo *philo, int debug);

//*** useful functions to synchro philos ***
void	wait_all_threads(t_table *table);
void	increase_long(pthread_mutex_t *mutex, long *value);
int		all_threads_running(pthread_mutex_t *mutex, long *threads, long philo_nbr);
void    thinking(t_philo *philo);
void    de_synchronize_philos(t_philo *philo);

//*** monitoring for deaths ***
void	*monitor_dinner(void *data);

#endif
