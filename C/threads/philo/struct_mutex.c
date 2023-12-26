//without dynamic allocation
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct data_s{
    int num;
    pthread_mutex_t mutex;
}data_t;

void *routine(void *arg)
{
data_t *data;
data = (data_t *)arg;
int i;
i = 0;
while (i < 1000000)
{
    pthread_mutex_lock(&data->mutex);
    data->num++;
    i++;
    pthread_mutex_unlock(&data->mutex);
}
return (NULL);
}

int main()
{
    data_t data;
    pthread_t t1, t2;
    data.num = 0;
    pthread_mutex_init(&data.mutex,NULL);

    if(pthread_create(&t1,NULL,routine,&data))
        return 1;
    if(pthread_create(&t2,NULL,routine,&data))
        return 2;
    if(pthread_join(t1,NULL))
        return 3;
    if(pthread_join(t2,NULL))
        return 4;

    printf("num>%d\n",data.num);
    pthread_mutex_destroy(&data.mutex);
    return 0;
}