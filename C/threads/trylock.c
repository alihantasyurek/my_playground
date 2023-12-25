#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;

void *routine(void* arg){
    pthread_mutex_lock(&mutex); // if you change it trylock it's gonna return a value instead of waiting other threads to finish.
    printf("Got lock\n");
    sleep(1);
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char **argv){
    pthread_t th[4];
    for(int i = 0; i < 4; i++){
        if(pthread_create(&th[i],NULL,&routine,NULL) != 0)
            perror("Error at creating thread");
    }
    for(int i = 0; i < 4; i++){
        if (pthread_join(th[i],NULL) != 0)
          perror("Error at joining thread");
    }
    pthread_mutex_destroy(&mutex);
return 0;
}