#include "main.h"
/**
 *
 * 
 * 
 * 
*/
void _execve(char **argv)
{
pid_t id;


id = fork();
if (id < 0)
{
perror ("fork");
    exit(EXIT_FAILURE);
}
if (id == 0)
{
   if(execve(argv[0], argv, NULL) == -1)
   {
    perror("excution");
    exit(EXIT_FAILURE);
   }
}
else
{
    wait(NULL);

}
}


