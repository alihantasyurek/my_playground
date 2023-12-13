#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *function(void *arg)
{
    int i = 0;
    int sum = 0;
    int index = *(int*)arg;
    while(i < 5)
    {
    sum += primes[index + i];
    i++;
    }
    printf("Local sum> %d\n",sum);
    *(int*)arg = sum;
    return arg;
}

int main()
{
    int i = 0;
    pthread_t t[2];

while(i < 2)
{

int *a = malloc(sizeof(int));
*a = i * 5;

if(pthread_create(t + i,NULL,&function,a) != 0)
    return 1;
i++;
}

i = 0;

int *r;
int globalSum;
while(i < 2)
{
if(pthread_join(*(t + i),(void **)&r) != 0)
    return 2;
globalSum += *r;
i++;
}
    printf("Global sum: %d\n", globalSum);
}