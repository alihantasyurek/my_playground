#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

// {
//int gettimeofday(struct timeval *tp, struct timezone *tz)
//getttimeoftheday will return 0 on success -1 on faiilure
//struct timezone is obsolete. This argument is for bakwards compatibility only.

//epoch time = 1 january 1970;

//     struct timeval {
//         time_t tv_sec; //used for seconds passed
// // number of seconds since the epoch time

//         suseconds_t tv_usec; //used for microseconds
// //additional microseconds after the number of seconds calculated since the epoch time;
// 1 sec = 1 000 000 microseconds.
// 1 sec = 1 000 miliseconds.
//     }
// 1 sec = 1000 ms 
// 1 sec = 1 000 000 mcs
// }

unsigned long time_milisec(void)
{
    struct timeval t;
    if(gettimeofday(&t,NULL)) // clever way to check - should use it more;
        return 0; //might be confusing because:
                 //gettimeofday returns 0 on success
                 //while this function returns 0 on failure;
    return((t.tv_sec * (unsigned long)1000) + (t.tv_usec / 1000));
}

void test(void)
{
    struct timeval td;
    unsigned long a,b;
    if(a = gettimeofday(&td,NULL))
    exit(1);
    a = td.tv_sec;

    b = time_milisec();
    if (b == 0)
    exit(2);
    printf("a(sec)>%lu\nb(ms)>%lu\n",a,b);

    a = time_milisec();
    usleep(10000); // gonna take microsec 10 000 mcs == 10 ms
    b = time_milisec();
    printf("time passed>%lums\n",b - a);
}

void time_print(void){
    struct timeval current_time;
    gettimeofday(&current_time,NULL);
    printf("sec: %ld\nmicrosec: %ld\n",current_time.tv_sec,current_time.tv_usec);
}

int main()
{
    time_print();
    test();
return 0;
}