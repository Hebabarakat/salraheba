#include"main.h"
/**
 *
 * 
 * 
 * 
 * 
*/
char ** strcut (char *lineptr)
{
char **argv;
int argc, i;
char *token;

argc = 1024;
i = 0;
argv = NULL;
argv = malloc(sizeof(char*) *argc);
if (argv == NULL)
{
    perror ("argv");
    exit(EXIT_FAILURE);
}
token = strtok(lineptr, DELMITER);
while(token)
{
    argv[i] = token;
    i++;
    token = strtok(NULL, DELMITER);
}
argv[i] = NULL;
return(argv);
}
