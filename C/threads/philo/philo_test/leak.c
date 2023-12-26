/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leak.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahinog <nsahinog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:48:49 by nsahinog          #+#    #+#             */
/*   Updated: 2023/11/23 17:48:51 by nsahinog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

void	free_memory(t_table *table)
{
	if (table ->forks)
	{
		free(table->forks);
		free(table->philos);
		free(table);
	}
	else
	{
		free(table->philos);
		free(table);
	}
}

void	destroy_mutex(t_table *table, int mutex_count)
{
	if (mutex_count >= 1)
		pthread_mutex_destroy(&table->stop_count);
	if (mutex_count >= 2)
		pthread_mutex_destroy(&table->count_eat);
	if (mutex_count >= 3)
		pthread_mutex_destroy(&table->eat_last);
	if (mutex_count >= 4)
		pthread_mutex_destroy(&table->is_print);
	if (mutex_count >= 5)
		pthread_mutex_destroy(&table->is_die);
}

void	destroy_forks(t_table *table, int i)
{
	int	j;

	j = 0;
	while (j < i)
		pthread_mutex_destroy(&table->forks[j++]);
}
