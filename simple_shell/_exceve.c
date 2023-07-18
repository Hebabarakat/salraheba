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
if (execve(path, argv, NULL) == -1)
{
	fprintf(stderr, "%s: command not found\n", argv[0]);
      printf("child process exit status: %d\n", 127);
      exit(127);
    }
  }
  else if (pid > 0)
  {
    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) {
      int exit_status = WEXITSTATUS(status);
      printf("parent process exit status: %d\n", exit_status);
    }
  }
    free(argv);
}


