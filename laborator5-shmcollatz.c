#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{
    int i;
    printf("Starting Parent: %d\n", getpid());

    
    if(shm_fd<0)
    {
        perror("Eroare la Crearea Memoriei Partajate.\n");
        return errno;
    }

    size_t page_size=getpagesize();
    size_t shm_size=page_size*argc; 
    if(ftruncate(shm_fd, shm_size)==-1) 
	{
		perror("Eroare la Alocarea de Memorie.\n");
		shm_unlink(shm_name); 
		return errno;
	}

	char *shm_ptr; 
	for(i=1; i<argc; i++)
    {
        shm_ptr=mmap(0, page_size, PROT_WRITE, MAP_SHARED, shm_fd, (i-1)*page_size);
        
        if(shm_ptr==MAP_FAILED)
		{
			perror("Nu s-a putut efectua impartirea memoriei in cadrul procesului.\n");
			shm_unlink(shm_name); //sterge memoria creata cu shm_open, in caz de eroare
			return errno;
		}

		pid_t pid=fork(); //creez un proces nou
        if(pid<0) {perror("Problema la PID.\n"); return errno;}
        else if(pid==0) 
        {
            int x=atoi(argv[i]);
            shm_ptr+=sprintf(shm_ptr, "%d: %d ", x, x); //incarcam in zona de memorie nr din ipoteza collatz
            while(x!=1)
            {
                if(x%2==0) x/=2;
                else x=3*x+1;
                shm_ptr+=sprintf(shm_ptr, "%d ", x);
            }
            printf("Done Parent %d Me %d\n",  getppid(), getpid());
            return 1;
        }

        munmap(shm_ptr, page_size); //nu mai am nevoie de zona de memorie incarcata
    }

    for(i=1; i<argc; i++) wait(NULL);

    for(i=1; i<argc; i++)
    {
        shm_ptr=mmap(0, page_size, PROT_READ, MAP_SHARED, shm_fd, (i-1)*page_size);
		printf("%s\n", shm_ptr);
		munmap(shm_ptr, page_size);
	}

	shm_unlink(shm_name);  
	printf("Done Parent %d Me %d\n", getppid(), getpid());

    return 0;
}