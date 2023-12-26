#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void *print_hello(void *arg){
    int i = 0;
    while(i < 100)
    {
    printf("Hello\n");
    i++;
    usleep(10000);
    }
    return (NULL);
}

void *print_world(void *arg){
    int i = 0;
    while(i < 100)
    {
    printf("\t\tWorld\n");
    i++;
    usleep(10000);
    }
    return (NULL);
}
int main()
{
// print_hello(NULL);
// print_world(NULL);
pthread_t t1;
pthread_t t2;

if(pthread_create(&t1,NULL,print_hello,NULL))
    return 1;
if(pthread_create(&t2,NULL,print_world,NULL))
    return 2;
// if(pthread_join(t1,NULL))
//     return 3;
// if(pthread_join(t2,NULL))
    // return 4;
printf("MAIN\n");
printf("MAIN\n");
printf("MAIN\n");
printf("MAIN\n");
printf("MAIN\n");
printf("MAIN\n");
printf("MAIN\n");
printf("MAIN\n");
return 0;
}