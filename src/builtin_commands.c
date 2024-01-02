#include "builtin_commands.h"

int is_builtin_command(const Command *command, const char *expected)
{
    return strcmp(command->command, expected) == 0;
}

void cd(const char *path)
{
    if (chdir(path) != 0)
    {
        perror("cd");
    }
}

void pwd()
{
    char cwd[MAX_INPUT_LENGTH];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("pwd");
    }
    else
    {
        printf("%s\n", cwd);
    }
}

int exit_shell(CommandSequence *sequence, int exit_code)
{
    if (sequence != NULL)
    {
        free_command_sequence(sequence);
    }
    free_aliases();
    exit(exit_code);
    return exit_code;
}

void echo(const Command *command)
{
    for (int i = 0; i < command->num_arguments; i++)
    {
        printf("%s ", command->arguments[i]);
    }
    printf("\n");
}

int execute_builtin_command(const Command *command, CommandSequence *sequence)
{
    if (is_builtin_command(command, "cd"))
    {
        if (command->num_arguments == 1)
        {
            cd(command->arguments[0]);
            return IS_BUILTIN_COMMAND;
        }
        perror("Usage: cd <directory>");
    }
    else if (is_builtin_command(command, "pwd"))
    {
        if (command->num_arguments == 0)
        {
            pwd();
            return IS_BUILTIN_COMMAND;
        }
        perror("Usage: pwd");
    }
    else if (is_builtin_command(command, "exit"))
    {
        if (command->num_arguments == 0)
        {
            exit_shell(sequence, EXIT_SUCCESS);
            return IS_BUILTIN_COMMAND;
        }
        perror("Usage: exit");
    }
    else if (is_builtin_command(command, "echo"))
    {
        if (command->num_arguments >= 1)
        {
            echo(command);
            return IS_BUILTIN_COMMAND;
        }
        perror("Usage: echo <message>");
    }
    else
    {
        return IS_NOT_BUILTIN_COMMAND;
    }

    return EXIT_FAILURE;
}
