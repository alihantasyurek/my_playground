/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atasyure <atasyure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:48:43 by nsahinog          #+#    #+#             */
/*   Updated: 2023/12/26 16:23:53 by atasyure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void	philo_init(t_philo *philo, t_table *table, int i)
{
	philo->id = i + 1;
	philo->table = table;
	philo->eat_count = 0;
	philo->last_eat = current_time();
	if (pthread_mutex_init(table->forks + i, NULL) != 0)
		destroy_forks(table, i);
}

void	fork_init(t_philo *philo, t_table *table, int i)
{
	if (i - 1 < 0)
		philo->rfork = table->forks + (table->number_of_philo - 1);
	else
		philo->rfork = table->forks + (i - 1);
	philo->lfork = table->forks + i;
}

static void	thread_init_utils(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->number_of_philo)
	{
		if (pthread_create(&table->philos[i].thread, NULL, philo_process, table->philos + i) != 0)
		{
			printf("error\n");
			return ;
		}
	}
}

void	thread_init(t_table *table)
{
	int	i;
	int	mutex_count;

	mutex_count = mutex_init(table);
	if (mutex_count != 5)
	{
		destroy_mutex(table, mutex_count);
		printf("erros\n");
		return ;
	}
	i = -1;
	while (++i < table->number_of_philo)
		philo_init(table->philos + i, table, i);
	i = -1;
	while (++i < table->number_of_philo)
		fork_init(table->philos + i, table, i);
	thread_init_utils(table);
	die_check(table);
}

int	mutex_init(t_table *table)
{
	int	result;

	result = 0;
	if (!pthread_mutex_init(&table->stop_count, NULL))
		result++;
	if (result == 1 && !pthread_mutex_init(&table->count_eat, NULL))
		result++;
	if (result == 2 && !pthread_mutex_init(&table->eat_last, NULL))
		result++;
	if (result == 3 && !pthread_mutex_init(&table->is_print, NULL))
		result++;
	if (result == 4 && !pthread_mutex_init(&table->is_die, NULL))
		result++;
	return (result);
}
