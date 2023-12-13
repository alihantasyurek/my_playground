#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void* routine(void* arg){
    sleep(1);
    int index = *(int*)arg;
    printf("%d\n",primes[index]);
    return NULL;
}

int main()
{
    pthread_t th[10];
    int i = 0;
    while (i < 10)
    {
    int *a = malloc(sizeof(int));
    *a = i;
    pthread_create(&th[i],NULL,&routine,(void*)a);
    i++;
    }

    i = 0;

    while(i < 10)
    {
    pthread_join(th[i],NULL);
    i++;
    }
}