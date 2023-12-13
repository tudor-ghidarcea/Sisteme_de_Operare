#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    write(1, "Hello World!\n", 13); 



	return 0;
}