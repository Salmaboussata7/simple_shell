#include "simple_shell.h"

/**
 * display_prompt - Display the shell prompt.
 */
void display_prompt(void)
{
printf("#cisfun$ ");
}

/**
 * read_command - Read the command entered by the user.
 *
 * Return: The command entered by the user.
 */
char *read_command(void)
{
char *command = NULL;
size_t bufsize = 0;

if (getline(&command, &bufsize, stdin) == -1)
{
if (feof(stdin))
{
printf("\n");
exit(EXIT_SUCCESS);
}
else
{
perror("read_command");
exit(EXIT_FAILURE);
}
}

return (command);
}

/**
 * parse_command - Parse the command into arguments.
 * @command: The command to parse.
 *
 * Return: An array of arguments.
 */
char **parse_command(char *command)
{
const char *delimiters = " \t\r\n\a";
char **args = NULL;
char *token = NULL;
int index = 0;

args = malloc(sizeof(char *) * 64);
if (args == NULL)
{
perror("parse_command");
exit(EXIT_FAILURE);
}

token = strtok(command, delimiters);
while (token != NULL)
{
args[index] = token;
index++;
token = strtok(NULL, delimiters);
}
args[index] = NULL;

return (args);
}

/**
 * execute_command - Execute the command.
 * @args: The arguments of the command.
 */
void execute_command(char **args)
{
pid_t pid;
int status;

pid = fork();
if (pid == -1)
{
perror("execute_command");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
/* Child process */
if (execvp(args[0], args) == -1)
{
perror("execute_command");
exit(EXIT_FAILURE);
}
}
else
{
/* Parent process */
do

{
waitpid(pid, &status, WUNTRACED);
} while (!WIFEXITED(status) && !WIFSIGNALED(status));
}
}

/**
 * free_memory - Free the allocated memory.
 * @command: The command to free.
 * @args: The arguments to free.
 */
void free_memory(char *command, char **args)
{
free(command);
free(args);
}
