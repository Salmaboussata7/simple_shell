#include "simple_shell.h"

/**
 * main - Entry point of the shell program.
 *
 * Return: Always 0.
 */
int main(void)
{
char *command = NULL;
char **args = NULL;
size_t bufsize = 0;

if (!isatty(STDIN_FILENO))
{
/* Non-interactive mode */
while (getline(&command, &bufsize, stdin) != -1)
{
args = parse_command(command);
execute_command(args);
free_memory(command, args);
command = NULL;
}
free_memory(command, args);
}
else
{
/* Interactive mode */
while (1)
{
display_prompt();
command = read_command();
args = parse_command(command);
execute_command(args);
free_memory(command, args);
}
}

return (0);
}
