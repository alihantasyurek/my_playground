#include "philo.h"
#include <stdio.h>

/*
 * 🚨 times in milliseconds 🚨
 * for the usleep function we need micro
 * so i immediately convert
 *  i use handy scientific notation 
 *  ~1e3 = 1_000
 *  ~1e6 = 1_000_000
 * 
 *
 * INPUT 
 * [0] ./philo
 * [1] number_of_philosophers
 * [2] time_to_die
 * [3] time_to_eat
 * [4] time_to_sleep
 * [5] [number_of_times_each_philosopher_must_eat]
 *
 * Check for max 200 philos
 * and timestamps > 60ms
 *
 * nbr_limit_meals -1 acts as a flag:
 * 	NO LIMITS
*/
