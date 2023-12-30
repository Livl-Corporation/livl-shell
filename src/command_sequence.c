#include "command_sequence.h"

void command_sequence_init(char *input)
{
    const char *delimeters = " \n";

    char *commands[MAX_COMMANDS];
    char *operators[MAX_OPERATORS];

    int command_count = 0;
    int operator_count = 0;
    char *currentCommand = NULL;

    CommandSequence sequence;
    sequence.commands = malloc(MAX_COMMANDS * sizeof(Command));
    sequence.operators = malloc(MAX_OPERATORS * sizeof(char *));
    sequence.num_commands = 0;

    char *token = strtok(input, delimeters);
    while (token != NULL)
    {
        if (command_count >= MAX_COMMANDS)
        {
            print_info("livl-shell$ is informing you that only the three first commands will be executed. Limit of commands reached.");
            break;
        }

        process_token(token, commands, operators, &currentCommand, &command_count, &operator_count);
        token = strtok(NULL, delimeters);

        if (token == NULL || get_operator_type(token) != UNKNOWN)
        {
            store_command(commands, &currentCommand, &command_count);
        }
    }

    // Build the command sequence with its commands
    for (int i = 0; i < command_count; i++)
    {
        sequence.commands[sequence.num_commands++] = evaluate_command(commands[i]);
        free(commands[i]);
    }

    // Build the command sequence with its operators
    for (int i = 0; i < operator_count; i++)
    {
        sequence.operators[i] = strdup(operators[i]);
        free(operators[i]);
    }

    evaluate_redirection(&sequence);

    int result = execute_command_sequence(&sequence);

    if (result < 0)
    {
        fprintf(stderr, "An error occurred while executing the commands\n");
    }

    free_command_sequence(&sequence);
}

void process_token(char *token, char **commands, char **operators, char **currentCommand, int *cmdIndex, int *opIndex)
{
    if (get_operator_type(token) != UNKNOWN)
    {
        operators[(*opIndex)++] = strdup(token);
        return;
    }

    // Token is a command
    if (*currentCommand == NULL)
    {
        *currentCommand = strdup(token);
    }
    else
    {
        size_t len = strlen(*currentCommand) + strlen(token) + 2;
        char *temp = realloc(*currentCommand, len);
        if (temp == NULL)
        {
            perror("realloc");
            return;
        }
        *currentCommand = temp;
        strcat(*currentCommand, " ");
        strcat(*currentCommand, token);
    }
}

void store_command(char **commands, char **currentCommand, int *cmdIndex)
{
    if (*currentCommand != NULL)
    {
        commands[(*cmdIndex)++] = *currentCommand;
        *currentCommand = NULL;
    }
}

void free_command_sequence(CommandSequence *sequence)
{
    for (int i = 0; i < sequence->num_commands; ++i)
    {
        free_command(&sequence->commands[i]);
    }
    free(sequence->commands);
}