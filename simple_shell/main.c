#include "main.h"
int main(void)
{
if (!isatty(STDIN_FILENO))
{
non_interactive();
}
else
{
char input[100];
char **args;
int i;
char c;
while(1)
{
write(1, "$ ", 2);
i = 0;
while(read(0, &c, 1) == 1)
{
if (c == '\n')
{
input[i] = '\0';
break;
}
input[i++] = c;
}
if (i== 0)
{
continue;
}
if (input[0] == 'e' && input[1] == 'x' && input[2] == 'i' && input [3] == 't')
{
break;
}
args = strcut (input);
_execve(args);
}
}
return 0;
}
