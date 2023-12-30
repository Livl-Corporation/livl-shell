#include "alias.h"

Alias *aliases;

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

    int i = 0;

    while (fgets(line, sizeof(line), file) != NULL && i < MAX_ALIASES)
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
            aliases[i].alias = malloc(sizeof(char) * (strlen(alias) + 1));
            aliases[i].command = malloc(sizeof(char) * (strlen(command) + 1));

            strcpy(aliases[i].alias, alias);
            strcpy(aliases[i].command, command);

            i++;
        }
    }

    fclose(file);
}

int get_alias(const char *name, char *command)
{
    for (int i = 0; i < MAX_ALIASES; ++i)
    {
        if (aliases[i].alias != NULL && strcmp(aliases[i].alias, name) == 0)
        {
            strcpy(command, aliases[i].command);
            return 1;
        }
    }
    return 0;
}