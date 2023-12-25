#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main(){
    char *a = "wtf";
    int fd;
    fd = open(a, O_RDONLY);
    if(!fd)
        perror("Error");
}