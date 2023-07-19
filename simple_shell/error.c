#include"main.h"

void execute_command(char* command, char* shell_name)
{
    int ret = execlp(command, command, NULL);
    if (ret == -1)
    {
        char error_message[100];
        sprintf(error_message, "%s: %d: %s: not found\n", shell_name, getpid(), command);
        write(2, error_message, strlen(error_message));
        exit(1);
    }
}

