#include"main.h"
/**
 *
 *
 *
 *
*/
void non_interactive (char *filename)
{
char *lineptr;
size_t n;
char **token;
FILE *file;

n = 0;
lineptr = NULL;
file = fopen(filename, "r");
if (file == NULL)
        {
        fprintf(stderr, "Error: Could not open file '%s': %s\n", filename, strerror(errno));
        exit(EXIT_FAILURE);
        }
token = malloc(sizeof (char *) * 2);
if (token == NULL)
{
    perror("token");
    exit(EXIT_FAILURE);
}
while (getline(&lineptr,&n,file) != -1)
{

    token = strcut(lineptr);
_execve(token);
}

 fclose(file);

 free (token);
free(lineptr);

}

