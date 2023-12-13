#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/errno.h>

int main()
{
    pid_t pid=fork(); 
    if(pid<0) {perror("Problema la PID.\n"); return errno;}
    else if(pid==0) 
    {
        char *argv[]={"ls", NULL}; 
        execve("/bin/ls", argv, NULL); 
        perror(NULL);
        
    }
    else 
    {
        printf("My PID=%d, Child PID=%d.\n", getppid(), getpid());
        wait(NULL); 
        printf("Child %d finished.\n",  getpid());
    }

    return 0;
}