#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define THREAD_NUM 2

void *routine(void* args){

}

int main(){
    pthread_t th[THREAD_NUM];
    int i; 
    for(i = 0; i < THREAD_NUM ;i++) {
        if(pthread_create(&th[i], NULL, &routine, NULL) != 0)
        {
        perror("Failed to create thread");
        return -1;
        }
    }

    for(i = 0; i < THREAD_NUM ;i++) {
        if(pthread_create(&th[i], NULL, &routine, NULL) != 0){
        perror("Failed to join thread");
        return -2;
        }
    }
return 0;
}