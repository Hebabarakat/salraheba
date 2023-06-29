#include<stdio.h>
#include <stdlib.h>
char *_strcpy(char *dest, char *src);

int main(void)
{
char *dest = NULL;
char *src = "hello world\n";
printf("src = %s", src);

dest = _strcpy(dest, src);

printf("dest = %s", dest);

return(0);
}

char *_strcpy(char *dest, char *src)
{       
        int i, n;
	printf("%s", src);
        n = 0; 
        while(src[n] != '\0')
        {
		n = n + 1;
	printf("%d\n", n);
        }
	dest = malloc(n+1);
	for (i = 0; i < n; i++)
	{      
        dest[i] = src[i];
	printf("%c\n", dest[i]); 
	}
        dest[i] = '\0';
	printf("%s", dest);
                return (dest);              
}

