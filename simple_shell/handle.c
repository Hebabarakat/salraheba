#include "main.h"
#include <string.h>

char *hpath(char **argv)
{
    int i;
    char **directories;
    char *cmd_path;
    char *path = my_getenv("PATH");
    if (path == NULL)
    {
        fprintf(stderr, "Error: PATH environment variable not set\n");
        return NULL;
    }

    directories = split_line(path);
    free(path);

    cmd_path = NULL;
    i = 0;
    while (directories[i] != NULL)
    {
        cmd_path = malloc(strlen(directories[i]) + strlen(argv[0]) + 2);
        if (cmd_path == NULL)
        {
            perror("Error allocating memory");
            free(directories);
            return NULL;
        }

        sprintf(cmd_path, "%s/%s", directories[i], argv[0]);

        if (access(cmd_path, X_OK) == 0)
        {
            free(directories);
            return cmd_path;
        }

        free(cmd_path);
        cmd_path = NULL;
        i++;
    }

    free(directories);

    fprintf(stderr, "Error: Command '%s' not found in PATH\n", argv[0]);
    return NULL;
}
