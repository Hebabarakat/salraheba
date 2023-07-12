#include "main.h"

int main()
{
char input[100];
char *args [20];
int status;
int i;
int j;
int k;
char c;

while(1)
{
write(1, "$ ", 2);
i = 0;
while(read(0, &c, 1) == 1);
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
j = 0;
for (k = 0; k < i; k++)
{
if (input [k] == ' ')
{
input [k] = '\0';
args[j++] = &input[k + 1];
}
}
args[j] = NULL;
pid_t pid = fork();
if (pid == -1)
{
write(2, "fork failed\n", 12);
continue;
}
if (pid == 0)
{
execv(input, args);
write(2, "execv failed\n", 13);
_exit(1);
}
wait(&status);
}
return (0);
}
