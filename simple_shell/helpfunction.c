#include"main.h"
/**
 *_realloc - Write a function that reallocates a memory block
 *@ptr: present the intger
 *@old_size: as a parameter
 *@new_size: as a parameter
 *Return: ptr always success
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *p;
	unsigned int i;

	if (new_size == old_size)
	{
		return (ptr);
	}
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	if (ptr == NULL)
	{
		p = malloc(new_size);
		if (p == NULL)
		{
			return (NULL);
		}
		return (p);
	}
	if (new_size > old_size)
	{
	p = malloc(new_size);
	if (p == NULL)
		return (NULL);
	for (i = 0; i < old_size; i++)
		*((char *)p + i) = *((char *)ptr + i);
	free(ptr);
	}
	return (p);
}
/**
 *_strcpy - write  a function that copying the string.
 * @dest: Describe the string 1
 * @src: Describe the string 2
 *
 * Return: Always dest (Success)
 */
char *_strcpy(char *dest, char *src)
{
int i, n;
n = 0;

while (src[n] != '\0')
{
n = n + 1;
}
dest = malloc(n + 1);
if (dest == NULL)
return (NULL);
for (i = 0; i < n; i++)
{
dest[i] = src[i];
}
dest[i] = '\0';
return (dest);
}
/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
/**
 * _strlen - writes the character c to stdout
 * @s : Decribe the char arry
 * Return: On success i.
 */
int _strlen(char *s)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
	{
	}
		return (i);
}
/**
 * _puts - writes the character c to stdout
 * @str : Decribe the char arry
 */
void _puts(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		_putchar(str[i]);
	}
}
/**
 *_strcmp  - write  a function that concatenates two strings.
 * @s1: Describe the string 1
 * @s2: Describe the string 2
 * Return: Always 0 (Success)
 */
int _strcmp(char *s1, char *s2)
{
	int i, n;

	for (i = 0; s1[i] != '='; i++)
{
	if (s1[i] == s2[i])
	n = 0;

	else
	n = -1;

}
	return (n);
}
