#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void noninteract(char *filename)
  {
    size_t n = 0;
    ssize_t nreads;
    char *lineptr = NULL;
    char **token;

<<<<<<< HEAD
    
=======
>>>>>>> 2cb2f37dc0ced11514e44b7b8160f91626ddfe60
    FILE *fp = fopen(filename, "r");
        printf("Processing file '%s'\n", filename);
    if (fp == NULL)
        {
        fprintf(stderr, "Error: Could not open file '%s': %s\n", filename, strerror(errno));
        exit(EXIT_FAILURE);
        }

    token = malloc(sizeof(char*) * 2);

    while ((nreads = getline(&lineptr, &n, fp)) != -1)
    {

        if (nreads == 1)
	{
        continue;
	}

	token = _strcut(lineptr);
	_exce(token);
	
    }

    free(lineptr);
    free(token);
    fclose(fp);
}

size_t _strcspn(const char *str, const char *ch)
{
const char *p, *q;
size_t count = 0;

for (p = str; *p != '\0'; p++)
{
for (q = ch; *q != '\0'; q++)
{
if (*p == *q)
{
return (count);
}
}
count++;
}
return (count);
}

