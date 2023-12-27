/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahinog <nsahinog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:49:00 by nsahinog          #+#    #+#             */
/*   Updated: 2023/11/23 17:49:02 by nsahinog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <pthread.h>

int	condition_check(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 5 && ac != 6)
		return (printf("Error: Number of arguments is not valid\n"), 0);
	while (av[++i])
		if (!number_check(av[i]))
			return (printf("Error: Arguments are must be digit\n"), 0);
	i = 0;
	while (av[++i])
		if (patoi(av[i]) <= 0)
			return (printf("Error: Invalid argument!\n"), 0);
	return (1);
}

t_table	*parse(int ac, char **av)
{
	t_table	*table;

	if (!condition_check(ac, av))
		return (NULL);
	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->number_of_philo = patoi(av[1]);
	table->time_to_die = patoi(av[2]);
	table->time_to_eat = patoi(av[3]);
	table->time_to_sleep = patoi(av[4]);
	table->number_of_must_eat = -1;
	if (ac == 6)
		table->number_of_must_eat = patoi(av[5]);
	table->philos = malloc(sizeof(t_philo) * table->number_of_philo);
	if (!table->philos)
		free(table);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->number_of_philo);
	if (!table->forks)
	{
		free_memory(table);
	}
	table->time = current_time();
	table->stop = 0;
	return (table);
}
