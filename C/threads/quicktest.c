#include <stdio.h>

int main()
{
    int array[5] = {0,3,6,69,31};
    int i = 0;
    while(i < 5)
    {
    printf("value>%d | adress>%p \n",array[i], array + i);
    i++;
    }
}