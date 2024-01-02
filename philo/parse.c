#include "philo.h"

//1) actual numbers
void parse_input(t_table *table,char **argv)
{
    table->philo_nbr = ft_atol(argv[1]);
    table->time_to_die = ft_atol(argv[2]);
    table->time_to_eat = ft_atol(argv[3]);
    table->time_to_sleep = ft_atol(argv[4]);
    if(argv[5])
        table->nbr_limit_meals = ft_atol(argv[5]);
    else 
        table->nbr_limit_meals = -1;
}