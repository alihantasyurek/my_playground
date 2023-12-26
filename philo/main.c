#include <stdio.h>
#include <stdlib.h>

void digit_control(char **argv)
{

}

int check_input(int argc,char **argv)
{
if (argc < 5 || argc > 6)
{
    printf("Wrong argument count\n");
    return (1);
}
if (digit_control(argv))
{
    return (1);
}


return (0);
}

void format_error(void)
{
printf("Usage with only integer characters:\n");
printf("./philo number_of_philosophers time_to_die ");
printf("time_to_eat time_to_sleep\n");
exit(1);
}

int main(int argc,char **argv)
{
if(check_input(argc,argv))
    format_error();
}