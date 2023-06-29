#include "main.h"
#include "string.h"
/**
*_getenv - Write your own getline function
*Return: environ[i] always success
*@name: Use a buffer to read many chars at once and call the least possible
*/
char *_getenv(char *name)
{
    int i;
    char *env_var;
    for (i = 0; environ[i] != NULL; i++) {
        if (strcmp(name, environ[i]) == 0) {
            env_var = strchr(environ[i], '=') + 1;
            return env_var;
        }
    }
    return NULL;
}
/**
 * char *_getenv(char *name)
{
int i;
for (i = 0; environ[i] != NULL; i++)
{
if (_strcmp(name, environ[i]) == 0)

return (environ[i]);
}
return (NULL);
}
*/
/**
 *hpath: You will need to use static variables
 */
char *hpath(char **argv)
{
    char *token;
    int check = 0;
    char *path;
    char *del = ":";
    char *cmd_path = NULL;
    
    path = _getenv("PATH");
    printf("%s\n", path);
    if (path == NULL)
    {
        fprintf(stderr, "Error: PATH environment variable not set\n");
        return NULL;
    }

    token = strtok(path, del);
    while (token)
    {
        cmd_path = malloc(strlen(token) + strlen(argv[0]) + 2);
        if (cmd_path == NULL)
        {
            perror("Error allocating memory");
            free(path);
            return NULL;
        }
        sprintf(cmd_path, "%s/%s", token, argv[0]);
        if (access(cmd_path, X_OK) == 0)
        {
            check = 1;
            break;
        }
        free(cmd_path);
        cmd_path = NULL;
        token = strtok(NULL, del);
    }
    free(path);
    
    if (!check)
    {
        fprintf(stderr, "Error: Command '%s' not found in PATH\n", argv[0]);
        return NULL;
    }
    return cmd_path;
}

int main (void)
{
	char *path;

	path = _getenv("PATH");
       printf("path = %s\n", path);
	
	return 0;
}
