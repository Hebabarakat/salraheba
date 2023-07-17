#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#define DELMITER " \t\r\n\a"
#define del "\n"
void read_noninteractiv(char *lineptr, ssize_t nreads);
extern char **environ;
char *handle_path(char *command);
char *_getenv(const char *name);
char *_readline(char c);
void _env(void);
void non_interactive (void);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void _execve(char **argv);
char ** strcut (char *lineptr);
/*strings.h*/
size_t _strlen(char*s);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, const char *src);
#endif
