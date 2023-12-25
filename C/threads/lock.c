#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* routine(void *arg){

}

int main(int argc, char **argv){
    pthread_t th[4];
    int i = 0;
    while(i < 4){
        if (pthread_create(th[i],NULL,&routine,NULL) != 0){
            perror("");
            return 1;
        }
    i++; 
    }

    i = 0;
    while(i < 4){
        if (pthread_join(th[i], NULL) != 0){
            perror("");
            return 2;
        }
    i++; 
    }
}