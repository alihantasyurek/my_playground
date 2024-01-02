/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahinog <nsahinog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:49:13 by nsahinog          #+#    #+#             */
/*   Updated: 2023/11/23 17:49:16 by nsahinog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

# define TOOK_THE_FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING	"is sleeping"
# define THINKING "is thinking"
# define DEAD "dead"

typedef struct s_philo
{
	struct s_table	*table;
	pthread_t		thread;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*pstop;
	uint64_t		id;
	uint64_t		last_eat;
	uint64_t		last_sleep;
	int				eat_count;
	int				sleeping;
	int				eating;
}	t_philo;

typedef struct s_table
{
	t_philo			*philos;
	int				number_of_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_must_eat;
	int				stop;
	uint64_t		time_to_die;
	uint64_t		time;
	pthread_mutex_t	stop_count;
	pthread_mutex_t	count_eat;
	pthread_mutex_t	eat_last;
	pthread_mutex_t	*forks;
	pthread_mutex_t	is_print;
	pthread_mutex_t	is_die;
}	t_table;

int			number_check(char *str);
int			check_die(t_table *table, int i);
int			must_eating_check(t_table *table);
int			condition_check(int ac, char **av);
void		philo_eat(t_philo *philo);
void		die_check(t_table *table);
void		thread_init(t_table *table);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);
void		*philo_process(void *_philo);
void		time_usleep(uint16_t micsec);
void		process_print(t_philo *philo, char *str);
void		fork_init(t_philo *philo, t_table *table, int i);
void		philo_init(t_philo *philo, t_table *table, int i);
t_table		*parse(int ac, char **av);
uint64_t	current_time(void);
uint64_t	time_from_start(t_table *table);
int			patoi(char *str);
void		free_memory(t_table *table);
void		destroy_mutex(t_table *table, int mutex_count);
void		destroy_forks(t_table *table, int i);
int			mutex_init(t_table *table);

#endif
