/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahinog <nsahinog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:48:32 by nsahinog          #+#    #+#             */
/*   Updated: 2023/11/23 17:48:34 by nsahinog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <unistd.h>

int	must_eating_check(t_table *table)
{
	int	i;

	if (table->number_of_must_eat < 0)
		return (0);
	i = 0;
	while (i < table->number_of_philo)
	{
		pthread_mutex_lock(&table->count_eat);
		if (table->philos[i++].eat_count < table->number_of_must_eat)
		{
			pthread_mutex_unlock(&table->count_eat);
			return (0);
		}
		else
			pthread_mutex_unlock(&table->count_eat);
	}
	return (1);
}

static void	die_utils(t_table *table, int i)
{
	process_print(table->philos + i, DEAD);
	pthread_mutex_lock(&table->stop_count);
	table->stop = 1;
	pthread_mutex_unlock(&table->stop_count);
	pthread_mutex_unlock(&table->eat_last);
}

int	check_die(t_table *table, int i)
{
	while (table->number_of_philo > 1)
	{
		i = -1;
		while (++i < table->number_of_philo)
		{
			pthread_mutex_lock(&table->eat_last);
			pthread_mutex_lock(&table->is_die);
			if ((current_time() - table->philos[i].last_eat)
				>= table->time_to_die)
			{
				die_utils(table, i);
				return (0);
			}
			else
				pthread_mutex_unlock(&table->eat_last);
			pthread_mutex_unlock(&table->is_die);
		}
		if (must_eating_check(table))
			break ;
		usleep(100);
	}
	return (1);
}

void	die_check(t_table *table)
{
	int	i;

	i = -1;
	if (table->number_of_philo == 1)
		process_print(table->philos, DEAD);
	if (!(check_die(table, i)))
		return ;
	pthread_mutex_lock(&table->stop_count);
	table->stop = 1;
	pthread_mutex_unlock(&table->stop_count);
}
