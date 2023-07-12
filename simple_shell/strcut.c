#include"main.h"
/**
 *
 * 
 * 
 * 
 * 
*/
#define MAX_ARGS 10
char ** strcut (char *lineptr)
{
char **argv;
int argc, i;
char *token;

argc = MAX_ARGS;
i = 0;
argv = NULL;
argv = malloc(sizeof(char*) *argc);
if (argv == NULL)
{
    perror ("argv");
    exit(EXIT_FAILURE);
}
token = strtok(lineptr,DELMITER);
while(token)
{
    argv[i] = token;
    i++;
    if (i >= argc)
{
argv = _realloc(argv, argc * sizeof(char *),(argc + 64)  * sizeof(char *));
if (argv == NULL)
{
perror("Allocation Error\n");
exit(EXIT_FAILURE);
}
}
    token = strtok(NULL, DELMITER);
}
argv[i] = NULL;
return(argv);
}

/**
 *_realloc - Write a function that reallocates a memory block
 *@ptr: present the intger
 *@old_size: as a parameter
 *@new_size: as a parameter
 *Return: ptr always success
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *p;
	unsigned int i;

	if (new_size == old_size)
	{
		return (ptr);
	}
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	if (ptr == NULL)
	{
		p = malloc(new_size);
		if (p == NULL)
		{
			return (NULL);
		}
		return (p);
	}
	if (new_size > old_size)
	{
	p = malloc(new_size);
	if (p == NULL)
		return (NULL);
	for (i = 0; i < old_size; i++)
		*((char *)p + i) = *((char *)ptr + i);
	free(ptr);
	}
	return (p);
}


