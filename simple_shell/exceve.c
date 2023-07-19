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

if (path)
{
	if (execve(path, argv, NULL) == -1)
{
	_printf("./hsh: %d: %s: not found\n",i, argv[0]);
      exit(127);
    }
}
else
{

	_printf("./hsh: %d: %s: not found\n",i, argv[0]);
	exit(127);
  }
}
else
  {
    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) {
      int exit_status = WEXITSTATUS(status);
    exit(exit_status);
    }
  }
    free(argv);
}


