#include "main.h"
/**
 *
 * 
 * 
 * 
*/
void _execve(char **argv)
{
pid_t pid;
int status;

pid = fork();
if (pid < 0)
{
perror ("fork");
    exit(EXIT_FAILURE);
}
if (pid == 0)
{
   if(execve(argv[0], argv, NULL) == -1)
   {
    perror("excution");
    exit(EXIT_FAILURE);
   }
}
else
{
    wait(&status);
    free(argv);
}
}


