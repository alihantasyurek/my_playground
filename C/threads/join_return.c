#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* roll_dice()
{
    int value = (rand() %6) + 1;
    int *result = malloc(sizeof(int));
    *result = value;
    
    return (void *) result;
}

int main(int argc, char **argv)
{
    int *value[5];
    srand(time(NULL));
    pthread_t t1[5];
    int i = 0;

    while (i < 5)
    {
        if (pthread_create(t1 + i, NULL,&roll_dice,NULL) != 0)
            return 1;
        i++;
    }
    i = 0;
    while (i < 5)
    {
    if (pthread_join(t1[i],(void **)value + i) != 0)
        return 2;
    i++;
    }
    i = 0;
    while (i < 5)
    {
     printf("%d\n",*value[i]);
     free(value[i]); // bad practise to allocate memory on one func, and deallcate on other
     i++;
    }
}