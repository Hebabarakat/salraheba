#include"main.h"
int _setenv(const char *name, const char *value, int write)
{
	int i, len =0, len2 = 0;
	 char *newvar;

	if (name == NULL || value == NULL)
	{
		return (-1);
	}


		len = _strlen((char *)name);
		len2 = _strlen((char *) value);
	while(environ[i])
	{
		if (strncmp(environ[i], name, len) == 0)
				
				{
				if (write)
				{
				newvar = malloc (len + len2+ 2);
				_strcpy(newvar, name);
				_strcat(newvar, "=");
				_strcat(newvar,(char*) value);
				environ[i] = newvar;
				free(newvar);
				return(0);
				}
	
				}
		i++;
	}
                                newvar = malloc (len + len2+ 2);
				_strcpy(newvar, name);
                                _strcat(newvar, "=");
                                _strcat(newvar,(char*) value);
                                environ[i] = newvar;
				environ[i + 1] = NULL;
				free(newvar);
                                return(0);

}

int _unsetenv(const char *name)
{
    int i, j, len = 0;

    if (name == NULL)
        return (-1);

    while (environ[i])
    {
        len = _strlen((char *)name);
        if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
        {
            for (j = i; environ[j]; j++)
                environ[j] = environ[j + 1];
            return (0);
        }
        i++;
    }

    return (-1);
}

void cd(char *path) 
{
    char *homedir, *prevdir, *cdbuffer ;
	size_t i;

	homedir = _getenv("HOME");
	prevdir = _getenv("OLDPWD");
	cdbuffer = NULL;
	i = 0;
    if (path == NULL || _strcmp(path, "~") == 0)
    {
        path = homedir;
    }
    else if (strcmp(path, "-") == 0) 
    {
        path = prevdir;
        _puts(path);
    }

    if (chdir(path) == -1) {
        perror("cd");
        exit(EXIT_FAILURE);
    }

    if (getcwd(cdbuffer, i) == NULL) {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }

    _setenv("OLDPWD", _getenv("PWD"), 1);
    _setenv("PWD", cdbuffer, 1);
}

