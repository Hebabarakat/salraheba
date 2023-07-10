#include "main.h"

int main(int argc, char **argv)
{
    if (argc  != 2)
    {
char input[50];
while (1)
{
printf ("$ ");
scanf ("%s", input);
}
    }
    else
    {
    non_interactive(argv[1]);
    }
return (0);
}
