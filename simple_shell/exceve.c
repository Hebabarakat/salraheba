#include "main.h"
/**
 *
 * 
 * 
 * 
*/
void _execve(char **argv, int i)
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
path = handle_path(argv[0], i);

	if (execve(path, argv, NULL) == -1)
{
	_printf("./hsh: %d: %s: not found\n",i, argv[0]);
  	exit(EXIT_FAILURE);
    }
}

else
  {
    waitpid(pid, &status, 0);
  }
}


