#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(/*int argc, char* argv[]*/)
{
	fork();
	printf("Hello world\n");
	return 0;
}
