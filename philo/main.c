/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atasyure <atasyure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:04:06 by atasyure          #+#    #+#             */
/*   Updated: 2024/01/03 17:41:53 by atasyure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//https://youtu.be/zOpzGHwJ3MU?t=5748
void	deallocate_all(t_table *table)
{
    if(table->philos)
        free(table->philos);
    if(table->forks)
        free(table->forks);
}

int main(int argc,char **argv)
{
    t_table table;
    table.philos = NULL; // Move it to an another function and initilize them there 
    table.forks = NULL; // after you made up your mind about how many mallocs you'll use

if(check_input(argc,argv))
{
    format_error();
    return 1;
}
// 1)errors checking, filling table table
parse_input(&table,argv);
// 2)creating the actual thing
if(data_init(&table))
{
    deallocate_all(&table);
    return 2;
}
if(dinner_start(&table))
{
    deallocate_all(&table);
    return 3;
}

deallocate_all(&table);

// No leaks -> philo full | 1 philo dies
// clean(&table);


return 0;
}
