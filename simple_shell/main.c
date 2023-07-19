#include "main.h"
int main(void)
{
if (!isatty(STDIN_FILENO))
{
non_interactive();
}
else
{
int i;
char *input;
char **args;
char c;
c = '\0';
i = 0;
while(1)
{
write(1, "$ ", 2);
i++;
input = _readline(c);
args = strcut (input);
_execve(args, i);
}
free(input);
}

return 0;
}
