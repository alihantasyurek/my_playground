/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahinog <nsahinog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:49:24 by nsahinog          #+#    #+#             */
/*   Updated: 2023/11/23 17:49:26 by nsahinog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

int	number_check(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	patoi(char *str)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	if (!str || *str < 0)
		return (0);
	if (str[0] == '+')
		i++;
	while (*(str + ++i))
		res = (res * 10) + (*(str + i) - '0');
	return (res);
}

void	process_print(t_philo *philo, char *str)
{
	uint64_t	i;

	i = time_from_start(philo->table);
	pthread_mutex_lock(&philo->table->is_print);
	pthread_mutex_lock(&philo->table->stop_count);
	if (!philo->table->stop)
		printf("%lu 	%lu %s\n", i, philo->id, str);
	pthread_mutex_unlock(&philo->table->stop_count);
	pthread_mutex_unlock(&philo->table->is_print);
}
