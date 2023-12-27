#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#define SUCCESS 0
#define FAILURE 1 

int digit_control(char **argv);
int check_input(int argc,char **argv);
int input_value(int argc,char **argv);
int	ft_atoi(const char *str);
void format_error(void);
#endif