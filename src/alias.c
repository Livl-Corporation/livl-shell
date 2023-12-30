#include "alias.h"

Alias *aliases;

void init_aliases()
{
    FILE *file = fopen(ALIASES_FILE, "r");
    if (file == NULL)
    {
        perror("Error opening aliases file for reading");
        return;
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

char *trim(char *str)
{
    char *end;

    // Trim leading whitespace
    while (isspace((unsigned char)*str))
        str++;

    if (*str == 0) // Only whitespace
        return str;

    // Trim trailing whitespace
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    // Null-terminate the trimmed string
    *(end + 1) = 0;

    return str;
}

int get_alias(char *name, char *command)
{
    for (int i = 0; i < MAX_ALIASES; ++i)
    {
        if (aliases[i].alias != NULL && strcmp(aliases[i].alias, name) == 0)
        {
            strcpy(command, aliases[i].command);
            printf("Alias found: %s\n", command);
            return 1;
        }
    }
    return 0;
}