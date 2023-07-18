#include "main.h"
char *handle_path(char *command)
{
char *command_path;
char *path;
char *dir;

/*check the command is fullpath*/
if (access(command, X_OK) == 0)
		{
		return (command);
		}
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
	_strcpy(command_path,dir);
 _strcat(command_path,"/");
 _strcat(command_path, command);

/* Check if command exists */

if (access(command_path, X_OK) == 0)
{
	return (command_path);

}
}
  /* Command not found */
fprintf(stderr, "%s: command not found\n", command);
return (NULL);
}

