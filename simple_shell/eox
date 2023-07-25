#include "main.h"

#define MAX_INPUT_LENGTH 100

int main()
{
char input[MAX_INPUT_LENGTH];
int status_code = 0;
int input_pos = 0;
int input_len = 0;
int input_arg_pos = -1;
int i;

/* Read user input one character at a time */
while (1)
{
char c = getchar();
if (c == '\n' || c == EOF) {
break;
}
if (input_pos >= MAX_INPUT_LENGTH - 1) {
fprintf(stderr, "Error: input too long\n");
exit(1);
}
input[input_pos++] = c;
}
input[input_pos] = '\0';
input_len = input_pos;

/* Parse input */
for (i = 0; i < input_len; i++) {
if (input[i] == ' ') {
input_arg_pos = i + 1;
break;
}
}
if (input_arg_pos != -1) {
status_code = atoi(input + input_arg_pos);
}

/* Handle exit command */
if (strcmp(input, "exit") == 0) {
exit(status_code);
}

/* Handle other commands */

return 0;
}
