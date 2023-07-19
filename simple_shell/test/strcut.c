#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

char **strcut(char *input)
{
  char **tokens = NULL;
  char *token;
  int i = 0;

  /* Allocate memory for an array of pointers to tokens */
  tokens = malloc(sizeof(char *));
  if (tokens == NULL)
  {
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  /* Split the input string into tokens */
  token = strtok(input, " \t\n");
  while (token != NULL)
  {
    /* Allocate memory for the token */
    tokens[i] = malloc(strlen(token) + 1);
    if (tokens[i] == NULL)
    {
      perror("malloc");
      exit(EXIT_FAILURE);
    }

    /* Copy the token into the array */
    strcpy(tokens[i], token);

    /* Get the next token */
    token = strtok(NULL, " \t\n");
    i++;

    /* Reallocate memory for the array of pointers to tokens */
    tokens = realloc(tokens, (i + 1) * sizeof(char *));
    if (tokens == NULL)
    {
      perror("realloc");
      exit(EXIT_FAILURE);
    }
  }

  /* Set the last element of the array to NULL */
  tokens[i] = NULL;

  return tokens;
}
