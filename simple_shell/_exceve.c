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
  if(execve(path, argv, NULL) == -1)
  {
	  perror("excution");
    exit(EXIT_FAILURE);
  }
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


