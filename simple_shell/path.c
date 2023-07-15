#include "main.h"
char *handle_path(char *command)
{
char *command_path;
char *path;
char *dir;

path = _getenv("PATH");
/* Split the path */
for (dir = strtok(path, ":"); dir != NULL; dir = strtok(NULL, ":"))
{
	/*Build the full path to the command */
command_path = malloc(strlen(path) + strlen(command) + 2);
if (command_path == NULL)
{
perror("malloc");
exit(1);
}
strcpy(command_path,dir);
strcat(command_path,"/");
strcat(command_path, command);

/* Check if command exists */

if (access(command_path, X_OK) == 0)
{
	return (command_path);
}
}
return(NULL);
}
