#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex;

void* routine() {
	pthread_mutex_lock(&mutex);
	for(int i = 0; i< 10000000; i++)
	mails++;
	pthread_mutex_unlock(&mutex);
}

int main(int argc, char* argv[]){
	pthread_mutex_init(&mutex, NULL);
	int i = 0;
	pthread_t th[4];
	while(i < 4)
	{
	if (pthread_create(th + i, NULL, &routine, NULL) != 0)  //First NULL is attributes, NULL is default 
	 	return 1;                                           // Last NULL is argument
		printf("Thread %d is created\n",i);
	if (pthread_join(th[i], NULL)) // NULL is the return value of the function
		return 2;
		printf("Thread %d is finished\n",i);
	i++;
	}
	i = 0;
	while(i < 4)
	{
		pthread_join(th[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n",mails);
		return 0;
}