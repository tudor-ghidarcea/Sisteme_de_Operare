#include <stdio.h>

int main(int argc, char *argv[])
{
	printf("Nr Argumente: %d\n", argc);
	printf("Nume Program: %s\n", argv[0]);
	for(int i=1; i<argc; i++)
        printf("Agumentul %d: %s\n", i, argv[i]);

	return 0;
}