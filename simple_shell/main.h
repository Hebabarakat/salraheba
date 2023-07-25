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
#include<stdarg.h>
#define DELMITER " \t\r\n\a"
#define del "\n"
/*advanced.c*/
int _setenv(const char *name, const char *value, int write);
int _unsetenv(const char *name);
void cd(char *path);

void read_noninteractiv(char *lineptr, ssize_t nreads);
extern char **environ;
char *handle_path(char *command, int i);
char *_getenv(const char *name);
char *_readline(char c);
int _putchar(char c);
void _puts(char *str);
void _env(void);
void non_interactive (void);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void _execve(char **argv, int i);
char ** strcut (char *lineptr);
void execute_command(char* command, char* shell_name);
int _strncmp(const char *str1, const char *str2, size_t n);
/*strings.h*/
size_t _strlen(char*s);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, const char *src);
int _strcmp(char *s1, char *s2);
/*printf*/
int _eputchar(char c);
int conv_c(va_list arg);
int conv_s(va_list arg);
int conv_p(va_list arg);
int conv_num_i(va_list arg);
int conv_num_d(va_list arg);
int _switch(va_list arg, char x);
int _printf(const char *format, ...);
#endif
