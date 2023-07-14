#include "main.h"
int main (void)
{
char *command = "ls";
char *path = getenv("PATH");
char *dir, *p;
/* Iterate over the directories in the PATH */
for (p = path; p = (*dir == '\0') ? (dir + 1) : (dir + 2))
{
dir = p;
/* Find the end of the current directory */
while (*p != '\0' && *p != ':')
P++;
}
/*Build the full path to the command */
char *command_path = malloc(p - dir + strlen(command) + 2);
if (comand_path == Null)
{
perror("malloc");
exit(1);
}
snprintf(commant_path, p - dir + strlen(command) + 2, "%.*s/%s", (int)(p - dir), dir, command);
/* Check if command exists */
if (access(command_path, X_OK) == 0)
{
/* The command exists, so fork and execute it */
pid_t pid = fork();
if (pid == -1)
{
perror("fork");
exit(1);
}
else if (pid == 0)
{
/* Child process */
execv(command_path, NULL);
/* execv() only returns if there's an error */
perror("execv");
exit(1);
}
else
{
/* Parent process */
int status;
wait(&status);
printf("Child process exited with status %d\n", status);
exit(0);
}
}
free(command_path);
/* If we've reached the end of the PATH, break out of the loop */
if (*p == '\0')
{
break;
}
}
printf("Command not found\n");
exit(1);
}
