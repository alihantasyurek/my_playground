/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duration.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahinog <nsahinog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:48:37 by nsahinog          #+#    #+#             */
/*   Updated: 2023/11/23 17:48:39 by nsahinog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <unistd.h>

void	philo_eat(t_philo *philo)
{
	if (philo->eat_count == philo->table->number_of_must_eat)
		return ;
	pthread_mutex_lock(philo->rfork);
	pthread_mutex_lock(philo->lfork);
	process_print(philo, TOOK_THE_FORK);
	process_print(philo, TOOK_THE_FORK);
	pthread_mutex_lock(&philo->table->count_eat);
	process_print(philo, EATING);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->table->count_eat);
	time_usleep(philo->table->time_to_eat);
	pthread_mutex_lock(&philo->table->eat_last);
	philo->last_eat = current_time();
	pthread_mutex_unlock(&philo->table->eat_last);
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(philo->lfork);
}

void	philo_sleep(t_philo *philo)
{
	process_print(philo, SLEEPING);
	time_usleep(philo->table->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	process_print(philo, THINKING);
}

void	*philo_process(void *_philo)
{
	t_philo	*philo;
	int		stop;

	philo = (t_philo *)_philo;
	if (philo->id % 2 == 0)
		time_usleep(10);
	while (1)
	{
		pthread_mutex_lock(&philo->table->stop_count);
		stop = philo->table->stop;
		pthread_mutex_unlock(&philo->table->stop_count);
		if (stop == 1)
			break ;
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
