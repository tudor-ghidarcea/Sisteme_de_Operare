#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <errno.h> 

int main(int argc, char **argv)
{
    if(argc!=3) {printf("Numar Gresit de Argumente. Incercati din Nou.\n"); return 0;}
    printf("Fisier Sursa: %s\n", argv[1]);
    printf("Fisier Copie: %s\n", argv[2]);

    int f1=open(argv[1], O_RDONLY);
    int f2=open(argv[2], O_WRONLY | O_CREAT, 200);
   
    if(f2 < 0)
    {
        perror("Eroare Deschidere Fisier Copie\n");
        return errno;
    }
    else
    {
        struct stat sb;
        if(stat(argv[1], &sb)) 
        {
            perror("Eroare Fisier de Intrare.\n");
            return errno;
        }
        printf("Fisierul de intrare ocupa %jd biti pe disk.\n", sb.st_size);
        int size = sb.st_size; 
        char buffer[size];
        read(f1, buffer, size);
        write(f2, buffer, size); 
    }
    close(f1); close(f2);

    return 0;
}