#include "main.h"
/**
 *
 *
 *
 *
 */
void noninteract(char *filename)
{	
	char *buf;
	ssize_t fd;
	ssize_t r;
	size_t letters = 100;
        int  count;
    	char **token = NULL;
	fd = open(filename, O_RDONLY);

	if (fd == -1)
	{
		exit(EXIT_FAILURE);
	}
	
	buf = malloc(sizeof(char) * letters);
	if (buf == NULL)
		exit(EXIT_FAILURE);

	r = read(fd, buf, letters);
    
	count = 1;
	  while (r);
   {
	token[0] =buf;
	 token[1] = NULL;
        _exce(token);
   	count++;
   }
free(buf);
close(fd);
}

