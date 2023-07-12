#include "main.h"
int main(void)
{
if (!isatty(STDIN_FILENO))
{
non_interactive();
}
else
{
char *input;
char **args;
char c;
c = '\0';
while(1)
{
write(1, "$ ", 2);
input = _readline(c);
args = strcut (input);
_execve(args);
}
free(input);
}

return 0;
}
