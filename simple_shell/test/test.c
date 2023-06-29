#include <stdio.h>

/*
Handle the PATH
fork must not be called if the command doesn’t exist
*/
int main()
{
char *path = getenv("PATH");
char *del = ":" ;
char *pathdir ;
char **argv = NULL;
 
printf("%s", path);
pathdir = strtok(path, del);
 argv[0] = "ls";
while (pathdir)
{
char *path = malloc(strlen(pathdir) + strlen(argv[0]) + 2);
sprintf(path, "%s/%s", pathdir, argv[0]);
}
 return (0);
}
