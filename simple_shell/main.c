#include "main.h"
int main(void)
{
	if (!isatty(STDIN_FILENO))
{
        non_interactive();
}


    return 0;
}

