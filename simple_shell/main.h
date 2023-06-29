#ifndef MAIN_H
#define MAIN_H
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#define DELIMITER " \t\r\n\a"
extern char **environ;
int my_strncmp(const char *s1, const char *s2, size_t n);
char *my_getenv(const char *name);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_strcpy(char *dest, char *src);
void _exce(char** token);
char** _strcut(char *lineptr);
int _putchar(char c);
int _strlen(char *s);
void _puts(char *str);
int _exec(char argv[]);
char** split_line(char *line);
 char *hpath(char **argv);
 void noninteract(char *filename);
 void _env(void);
#endif
