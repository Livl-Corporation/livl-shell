#include "command.h"

Command evaluate_command(const char *input)
{
    Command cmd;
    init_command(&cmd);

    // Copy the input for manipulation
    char *input_copy = strdup(input);

    // Handle aliases
    parse_aliases(input_copy);
   
    // Tokenize by spaces, tabs, and newline characters
    char *token = strtok(input_copy, CMD_DELIMITERS);

    // 1. The first part is the command (from the first letter to the one of the first delimiters)
    if (token == NULL)
    {
        perror("strtok");
        free(input_copy);
        return cmd;
    }

    cmd.command = strdup(token);

    // 2. After getting the command name, collect all arguments (each token = 1 argument depending on the delimiters)
    while ((token = strtok(NULL, CMD_DELIMITERS)) != NULL)
    {
        handle_quotes(token);
        cmd.arguments = realloc(cmd.arguments, (cmd.num_arguments + 1) * sizeof(char *));
        cmd.arguments[cmd.num_arguments] = strdup(token);
        cmd.num_arguments++;
    }

    // Add NULL at the end of the arguments array for execvp
    cmd.arguments = realloc(cmd.arguments, (cmd.num_arguments + 1) * sizeof(char *));
    cmd.arguments[cmd.num_arguments] = NULL;

    // Get the complete command
    get_complete_command_array(&cmd);
    cmd.input_string = strdup(input);

    free(token);
    free(input_copy);
    return cmd;
}

void get_complete_command_array(Command *cmd)
{
    char **new_arguments = malloc((cmd->num_arguments + 2) * sizeof(char *));
    if (new_arguments == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    new_arguments[0] = strdup(cmd->command);
    for (int i = 0; i < cmd->num_arguments; ++i)
    {
        new_arguments[i + 1] = strdup(cmd->arguments[i]);
    }
    new_arguments[cmd->num_arguments + 1] = NULL;
    
    cmd->complete_command = new_arguments;
}

void init_command(Command *cmd)
{
    cmd->command = NULL;
    cmd->arguments = NULL;
    cmd->complete_command = NULL;
    cmd->input_string = NULL;
    cmd->redirection.input_file = NULL;
    cmd->redirection.output_file = NULL;
    cmd->redirection.append_input = 0;
    cmd->redirection.append_output = 0;
    cmd->num_arguments = 0;
}

void free_command(Command *cmd)
{
    free(cmd->command);
    cmd->command = NULL;

    for (int i = 0; i < cmd->num_arguments; ++i)
    {
        free(cmd->arguments[i]);
        cmd->arguments[i] = NULL;
    }
    free(cmd->arguments);
    cmd->arguments = NULL;

    free(cmd->redirection.input_file);
    cmd->redirection.input_file = NULL;

    free(cmd->redirection.output_file);
    cmd->redirection.output_file = NULL;

    free(cmd->complete_command);
    cmd->complete_command = NULL;

    free(cmd->input_string);
    cmd->input_string = NULL;
}
