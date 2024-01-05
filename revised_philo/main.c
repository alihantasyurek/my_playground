#include "philo.h"

/*
 * INPUT
 *
 * ./philo 5 800 200 200 [7]
*/
void	format_input(t_table *table, char **argv)
{
	table->philo_nbr = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1000; //reverting to microsec find out why?
	table->time_to_eat = ft_atol(argv[3]) * 1000;
	table->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (argv[5])
		table->nbr_limit_meals = ft_atol(argv[5]);
	else
		table->nbr_limit_meals = -1;
}

int	main(int argc, char **argv)
{
	t_table	table;

 if(check_input(argc,argv))
{
    format_error();
    return 1;
}
format_input(&table,argv);

if(data_init(&table))
	return 2;
dinner_start(&table);
clean(&table);
}
