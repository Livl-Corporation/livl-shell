#include "alias.h"

Alias *aliases;
int num_aliases;

void init_aliases()
{
    FILE *file = fopen(ALIASES_FILE, "r");
    if (file == NULL)
    {
        // Create the alias file if it doesn't exist
        file = fopen(ALIASES_FILE, "w");
        if (file != NULL)
        {
            fclose(file);
        }
        else
        {
            perror("Error creating aliases file.");
        }
    }

    aliases = malloc(sizeof(Alias) * MAX_ALIASES);

    char line[MAX_INPUT_LENGTH];

    num_aliases = 0;

    while (fgets(line, sizeof(line), file) != NULL && num_aliases < MAX_ALIASES)
    {
        // Extract alias and command from line
        char *alias = strtok(line, "=");
        char *command = strtok(NULL, "=");

        // Remove leading and trailing whitespace from alias and command
        alias = trim(alias);
        command = trim(command);
        handle_quotes(command);

        if (alias != NULL && command != NULL)
        {
            aliases[num_aliases].alias = malloc(sizeof(char) * (strlen(alias) + 1));
            if (aliases[num_aliases].alias == NULL)
            {
                perror("malloc");
                exit(EXIT_FAILURE);
            }

            aliases[num_aliases].command = malloc(sizeof(char) * (strlen(command) + 1));
            if (aliases[num_aliases].command == NULL)
            {
                perror("malloc");
                exit(EXIT_FAILURE);
            }

            strcpy(aliases[num_aliases].alias, alias);
            strcpy(aliases[num_aliases].command, command);

            num_aliases++;
        }
    }

    fclose(file);
}

int is_alias(const char *name, char *command)
{
    for (int i = 0; i < num_aliases; ++i)
    {
        if (aliases[i].alias != NULL && strcmp(aliases[i].alias, name) == 0)
        {
            strcpy(command, aliases[i].command);
            return IS_ALIAS_COMMAND;
        }
    }
    return IS_NOT_ALIAS_COMMAND;
}

void free_aliases()
{
    for (int i = 0; i < num_aliases; ++i)
    {
        free(aliases[i].alias);
        free(aliases[i].command);
    }
    free(aliases);
}

void parse_aliases(char *input)
{
    char *token = strtok(input, CMD_DELIMITERS);
    char replaced_input[MAX_INPUT_LENGTH] = ""; // Initialize a new string to store the replaced input

    char command[MAX_INPUT_LENGTH];
    if (is_alias(token, command) == IS_ALIAS_COMMAND)
    {
        strcat(replaced_input, command); // Append the replaced command to the new string
    }
    else
    {
        strcat(replaced_input, token); // Append the original token to the new string
    }

    strcat(replaced_input, " ");                       // Add a space between tokens
    strcat(replaced_input, input + strlen(token) + 1); // Append the remaining input after the first token
    strcpy(input, replaced_input);                     // Copy the replaced input back to the original input string
}