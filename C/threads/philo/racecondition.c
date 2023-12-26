#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t mutex;
void *routine(void *arg)
{
int *num;
int i;
i = 0;
num = (int *)arg;

while (i < 1000000)
{
    pthread_mutex_lock(&mutex);
    (*num)++;
    i++;
    pthread_mutex_unlock(&mutex);
}
return (NULL);
}

void error_exit(int *num){
    free(num);
    exit(10);
}

int main(void)
{
pthread_mutex_init(&mutex,NULL);
    int *num;
    pthread_t t1,t2;
    num = malloc(sizeof(int));
    if(!num)
        exit(1);
    *num = 0;
    if(pthread_create(&t1,NULL,routine,num))
        error_exit(num);
    if(pthread_create(&t2,NULL,routine,num))
        error_exit(num);
    if(pthread_join(t1,NULL))
        error_exit(num);
    if(pthread_join(t2,NULL))
        error_exit(num);
    printf("NUM: %d\n", *num);
pthread_mutex_destroy(&mutex);
        error_exit(num);
}