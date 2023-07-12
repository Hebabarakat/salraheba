#include"main.h"
/**
 *
 *
 *
 *
*/
void non_interactive (void)
{
char *ptr;
char c;
char **token;
int i;
c = '\0';
ptr =_readline(c);

while (ptr)
{
	 if (ptr[strlen(ptr) - 1] == '\n')
        {
            ptr[strlen(ptr) - 1] = '\0';
	    i++;
        }
}
while(i != 0)
{

    token = strcut(ptr);
    if (token == NULL)
    {
   perror ("token");
   exit (EXIT_FAILURE);
    }
_execve(token);
i--;
}

}

