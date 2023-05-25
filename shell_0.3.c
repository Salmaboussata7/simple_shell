#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 64

/**
 * Executes the given command. 
 * @param command The command to execute.
 * @return Returns 0 on success, or 1 on failure.
 */
int execute_command(char *command);

/**
 * Entry point of the program.
 */
int main(void)
{
char command[MAX_COMMAND_LENGTH];

while (1)
{
printf(":) ");
fflush(stdout);

if (fgets(command, sizeof(command), stdin) == NULL)
{
printf("\n");
break;
}

command[strcspn(command, "\n")] = '\0';

if (strcmp(command, "exit") == 0)
{
break;
}

execute_command(command);
}

return (0);
}

/**
 * Executes the given command.
 * @param command The command to execute.
 * @return Returns 0 on success, or 1 on failure.
 */
int execute_command(char *command)
{
pid_t pid;
char *arguments[MAX_ARGUMENTS];
char *token;
int arg_count = 0;

token = strtok(command, " ");
while (token != NULL)
{
arguments[arg_count] = token;
arg_count++;

if (arg_count >= MAX_ARGUMENTS - 1)
{
printf("Too many arguments\n");
return (1);
}

token = strtok(NULL, " ");
}
arguments[arg_count] = NULL;

char *path = getenv("PATH");
char *path_token = strtok(path, ":");
while (path_token != NULL)
{
char *executable = malloc(strlen(path_token) + strlen(arguments[0]) + 2);
sprintf(executable, "%s/%s", path_token, arguments[0]);

if (access(executable, X_OK) == 0)
{
pid = fork();
if (pid == 0)
{

execve(executable, arguments, NULL);
perror("execve");
exit(1);
}
else if (pid > 0)
{

int status;
waitpid(pid, &status, 0);
return (0);
}
else
{
perror("fork");
return (1);
}
}

free(executable);
path_token = strtok(NULL, ":");
}

printf("%s: command not found\n", arguments[0]);
return (1);
}
