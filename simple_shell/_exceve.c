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
char* path;

pid = fork();
if (pid < 0)
{
perror ("fork");
    exit(EXIT_FAILURE);
}
if (pid == 0)
{
path = handle_path(argv[0]);
if (path)
{
   execve(path, argv, NULL);
}
   else
   {
    perror("command not found");
    exit(EXIT_FAILURE);
   }
}
else
{
    wait(&status);
    free(argv);
}
}


