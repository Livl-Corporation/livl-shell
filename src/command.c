#include "command.h"

Command evaluate_command(const char *input)
{
    Command cmd;
    init_command(&cmd);

    char delimiters[] = " \t\n";

    // Copy the input for manipulation
    char *input_copy = strdup(input);

    // Tokenize by spaces, tabs, and newline characters
    char *token = strtok(input_copy, delimiters);

    // 1. The first part is the command (from the first letter to the one of the first delimiters)
    if (token != NULL)
    {
        cmd.command = strdup(token);
    }
    else
    {
        perror("strtok");
        free(input_copy);
        return cmd;
    }

    // 2. After getting the command name, collect all arguments (each token = 1 argument depending on the delimiters)
    while ((token = strtok(NULL, delimiters)) != NULL)
    {
        handle_quotes(&token);
        cmd.arguments = realloc(cmd.arguments, (cmd.num_arguments + 1) * sizeof(char *));
        cmd.arguments[cmd.num_arguments] = strdup(token);
        cmd.num_arguments++;
    }

    // Add NULL at the end of the arguments array for execvp
    cmd.arguments = realloc(cmd.arguments, (cmd.num_arguments + 1) * sizeof(char *));
    cmd.arguments[cmd.num_arguments] = NULL;

    // Get the complete command
    cmd.complete_command = get_complete_command_array(&cmd);
    cmd.input_string = strdup(input);

    free(input_copy);
    return cmd;
}

void handle_quotes(char **token)
{
    char quote_type = (*token)[0];
    if (quote_type == '"' || quote_type == '\'')
    {
        char *end_quote = strchr(&(*token)[1], quote_type);

        if (end_quote != NULL)
        {
            *end_quote = '\0'; // Remove the quotation mark
            (*token)++;        // Skip the initial quotation mark
        }
    }
}

char **get_complete_command_array(Command *cmd)
{
    char **new_arguments = malloc((cmd->num_arguments + 2) * sizeof(char *));
    if (new_arguments == NULL)
    {
        perror("malloc");
        free_command(cmd);
        exit(EXIT_FAILURE);
    }
    new_arguments[0] = cmd->command;
    for (int i = 0; i < cmd->num_arguments; ++i)
    {
        new_arguments[i + 1] = cmd->arguments[i];
    }
    return new_arguments;
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
    for (int i = 0; i < cmd->num_arguments; ++i)
    {
        free(cmd->arguments[i]);
    }
    free(cmd->arguments);
    free(cmd->redirection.input_file);
    free(cmd->redirection.output_file);
    free(cmd->complete_command);
    free(cmd->input_string);
}