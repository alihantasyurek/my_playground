#include "philo.h"

void  assign_forks(t_philo *philo, t_fork *forks,
   int philo_index_pos)
{
   int   philo_nbr;

   philo_nbr = philo->table->philo_nbr;

   philo->right_fork = &forks[(philo_index_pos + 1) % philo_nbr];
   philo->left_fork = &forks[philo_index_pos];
   if (philo->id % 2 == 0)
   {
   philo->right_fork = &forks[philo_index_pos];
   philo->left_fork = &forks[(philo_index_pos + 1) % philo_nbr];
   }
}

void  philo_init(t_table *table)
{
   int   i;
   t_philo *philo;

   i = -1;
   while(++i < table->philo_nbr)
   {
      philo = table->philos + i;
      philo->id = i + 1;
      philo->is_full = -1;
      philo->meals_counter = 0;
      // 	safe_mutex_handle(&philo->philo_mutex, INIT);
      philo->table = table;
      assign_forks(philo, table->forks, i);
   }
}

int data_init(t_table *table)
{
 int i; 
 i = -1;
 table->end_simulation = FAILURE;
 table->all_threads_ready = FAILURE;

 if (pthread_mutex_init(&table->print_mutex,NULL))
    return FAILURE;
 if (pthread_mutex_init(&table->table_mutex,NULL))
    return FAILURE;

 table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
 if(!table->philos)
    return FAILURE;

 table->forks = malloc(sizeof(t_fork) * table->philo_nbr);
 if(!table->forks)
    return FAILURE;

 while(++i < table->philo_nbr)
 {
   if(pthread_mutex_init(&table->forks[i].fork, NULL))
      return FAILURE;
   table->forks[i].fork_id = i;
 }
philo_init(table);

return SUCCESS;
}