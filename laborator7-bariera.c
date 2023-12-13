#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <semaphore.h>
#include <pthread.h>
#define NTHRS 5

sem_t sem; 
pthread_mutex_t mtx; 
int S=0;

void barrier_point()
{
    int S_local;
    pthread_mutex_lock(&mtx);
    S++;
    pthread_mutex_unlock(&mtx);
    S_local=S;

    if(S_local<NTHRS) 
        if(sem_wait(&sem)) {perror(NULL); return errno;}
        else;
    else for(int i=0; i<NTHRS; ++i) sem_post(&sem); 
}
void *tfun(void *v)
{
	int *tid=(int *)v;
	printf("%d reached the barrier \n",*tid);
	barrier_point();
	printf("%d passed the barrier \n", *tid);

	free(tid);
	return NULL;
}


int main()
{
    pthread_t thr[10];
	int i;

	if(sem_init(&sem, 0, S)) 
	{perror(NULL); return errno;}

	if(pthread_mutex_init(&mtx, NULL)) 
	{perror(NULL); return errno;}

	for(i=0; i<NTHRS; i++)
	{
        int *k=(int *)malloc(1);
        *k=i;
		if(pthread_create(&thr[i], NULL, tfun, k))
        {perror(NULL); return errno;}
	}

    for(i=0; i<NTHRS; i++)
        if(pthread_join(thr[i], NULL))
        {perror(NULL); return errno;}

    sem_destroy(&sem); 
    pthread_mutex_destroy(&mtx); 

    return 0;
}