#include"main.h"
/**
 *
 *
 *
 *
*/
void non_interactive (char *filename)
{
int i; 
ssize_t nreads;
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
nreads = getline(&lineptr,&n, file);
while (nreads != -1)
{
    if (nreads == 1)
    {
        continue;
    }
    token = strcut(lineptr);
_execve(token);
}


 fclose(file);

for (i = 0; token[i] !=(void *) '\0'; i++)
{
 free(token[i]);
}
 free (token);
 free (lineptr);
lineptr = NULL;

}

