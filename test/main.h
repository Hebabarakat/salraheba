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

char *my_getenv(const char *name);
int my_strncmp(const char *s1, const char *s2, size_t n);
char **split_line(char *line);
#endif
