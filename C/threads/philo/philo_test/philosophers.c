/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahinog <nsahinog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:49:06 by nsahinog          #+#    #+#             */
/*   Updated: 2023/11/23 17:49:08 by nsahinog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <stdlib.h>

void	thread_term(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->number_of_philo)
	{
		if (table->number_of_philo == 1)
			pthread_detach(table->philos[i].thread);
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			break ;
	}
	destroy_mutex(table, 5);
	destroy_forks(table, table->number_of_philo);
	free_memory(table);
}

int	main(int ac, char **av)
{
	t_table	*table;
	int		i;

	table = parse(ac, av);
	if (table == NULL)
		return (0);
	if (table->number_of_philo == 1)
	{
		time_usleep(table->time_to_die);
		i = time_from_start(table);
		printf("%d %d %s\n", 0, 1, TOOK_THE_FORK);
		printf("%d %d %s\n", i, 1, DEAD);
		free_memory(table);
	}
	if (table != NULL)
	{
		if (table->number_of_philo > 1)
		{
			thread_init(table);
			if (table)
				thread_term(table);
		}
	}
	return (0);
}
