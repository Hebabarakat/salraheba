int exit_status (char *input)
{
token = strtok(input, " ");
if (strcmp(token, "exit") ==0)
{
/*Handle exit command*/
token = strtok(NULL, " ");
if (token != NULL)
{
/*If argument is provided, convert it to integer and use it as exit status*/
int exit_status = atoi(token);
exit(exit_status);
}
else
{
/*If no argument is provided, use default exit status of 0*/
exit(0);
}
}
