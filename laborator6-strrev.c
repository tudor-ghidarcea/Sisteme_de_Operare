#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>

void *oglinda(void *sir)
{
    char *s=(char *)sir, *aux=(char*)malloc(strlen(s));
	for(int i=strlen(s)-1; i>=0; i--) aux[strlen(s)-1-i]=s[i];
	return aux;
}

int main(int argc, char *argv[])
{
    char *result;

    pthread_t thr;
    if(pthread_create(&thr, NULL, oglinda, argv[1]))
    
    {
        perror("Nu s-a putut crea thread-ul.\n");
        return errno;
    }

    
    if(pthread_join(thr, &result))
    {
		perror("Eroare.\n");
		return errno;
	}

	printf("%s\n", result);
	free(result); 

    return 0;
}