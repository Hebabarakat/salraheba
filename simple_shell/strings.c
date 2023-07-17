#include "main.h"
/**
 *
 *
 *
 */
size_t _strlen(char *s)
{
	size_t i;
	for (i = 0; s[i] != '\0'; i++)
			;
	return (i);
}

/**
 *
 *
 *
 */
char *_strcat(char *dest, char *src)
{
	size_t i,j, len, sumlen;

       len = _strlen(dest);
        sumlen = len + (_strlen(src));
   	
	 j = 0;     
        for (i = len; i <= sumlen;  i++)
        {
        dest[i] = src[j];
	j++;
        }
	return (dest);
        
}
char *_strcpy(char *dest, const char *src)
{
	size_t i;
	
	i = 0;
	while(src[i])
{

	dest[i] = src[i];
	i++;
}
dest[i] = '\0';

	return(dest);
}
