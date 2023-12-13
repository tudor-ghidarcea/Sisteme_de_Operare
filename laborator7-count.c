#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#define MAX_RESOURCES 5

int available_resources=MAX_RESOURCES;
pthread_mutex_t mtx; 

int decrease(int count) 
{
    pthread_mutex_lock(&mtx); 
    if(available_resources<count)
    {
        pthread_mutex_unlock(&mtx); 
        return -1;
    }
    else
    {
        available_resources -= count;
        printf("Got %d resources, remaining %d resources\n", count, available_resources);
    }
    pthread_mutex_unlock(&mtx); 

    return 0;
}
int increase(int count) 
{
    pthread_mutex_lock(&mtx); 
    available_resources += count ;
    printf("Release %d resources, remaining %d resources\n", count, available_resources);
    pthread_mutex_unlock(&mtx); 

    return 0;
}
void *functie(void *arg) 
{
    int count=(int)arg;
    decrease(count);
    increase(count);

    return NULL;
}

int main()
{
    if(pthread_mutex_init(&mtx, NULL)) 
    {
          perror("Eroare Creare Mutex.\n");
          return errno ;
    }

    printf("MAX_RESOURCES = %d\n", available_resources);

    pthread_t tid[7]; //7 fire de executie
    int i, count;
    for(i=0; i<7; i++)
    {
        count=rand()%(MAX_RESOURCES + 1);
        if(pthread_create(&tid[i], NULL, functie, count))
       
        {
            perror("Nu s-a putut crea thread-ul.\n");
            return errno;
        }
    }

    for(i=0; i<7; i++)
    {
        if(pthread_join(tid[i], NULL)) 
        {
            perror("Eroare.\n");
            return errno;
        }
    }

    pthread_mutex_destroy(&mtx);

    return 0;
}