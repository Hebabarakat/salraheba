#include "main.h"
#include "string.h"
char *hpath(char **argv)
{
    char **token;
    int check = 0;
    char *path;
    char *cmd_path = NULL;
    int i;
    path = my_getenv("PATH");
    if (path == NULL)
    {
        fprintf(stderr, "Error: PATH environment variable not set\n");
        return NULL;
    }
	token = split_line(path);
    while (token)
    {
        cmd_path = malloc(strlen(token[i]) + strlen(argv[0]) + 2);
        if (cmd_path == NULL)
        {
            perror("Error allocating memory");
            free(path);
            return NULL;
        }
        sprintf(cmd_path, "%s/%s", token[i], argv[0]);
        if (access(cmd_path, X_OK) == 0)
        {
            check = 1;
            break;
        }
	i++;
        free(cmd_path);
        cmd_path = NULL;
    }
    free(path);
    
    if (!check)
    {
        fprintf(stderr, "Error: Command '%s' not found in PATH\n", argv[0]);
        return NULL;
    }
    return cmd_path;
}
