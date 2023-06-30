#include "main.h"


int main(int argc, char **argv)
{
	int i;
	char *path = my_getenv("PATH");
	char **splitted = split_line(path);
	for(i = 0; splitted[i];i++) {
		printf("%s\n",splitted[i]);
	}
	printf("argc: %d\n,argv: %s\n, PATH: %s\n", argc,argv[0],path);

	return 0;
}

