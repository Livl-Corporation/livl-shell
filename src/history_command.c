#include "history_command.h"

CommandHistory command_history;

void init_command_history()
{
    command_history.history_count = 0;
    command_history.current_index = -1;
    load_command_history_from_file();
}

void add_to_command_history(const char *command)
{
    if (command_history.history_count < MAX_HISTORY_SIZE)
    {
        strcpy(command_history.history[command_history.history_count], command);
        command_history.history_count++;
        command_history.current_index = command_history.history_count;
        save_command_history_to_file();
    }
    else
    {
        printf("History is full. Delete your history.txt file.\n");
    }
}

void get_previous_command(char *input)
{
    if (command_history.current_index > 0)
    {
        command_history.current_index--;
        strcpy(input, command_history.history[command_history.current_index]);
    }
    else
    {
        strcpy(input, "");
    }
}

void get_next_command(char *input)
{
    if (command_history.current_index < command_history.history_count - 1)
    {
        command_history.current_index++;
        strcpy(input, command_history.history[command_history.current_index]);
    }
    else
    {
        command_history.current_index = command_history.history_count;
        strcpy(input, "");
    }
}

void save_command_history_to_file()
{
    FILE *file = fopen(HISTORY_FILE, "a"); // Open in append mode
    if (file == NULL)
    {
        perror("Error opening history file for writing");
        return;
    }

    // Save the new command if it's not already in the history
    if (command_history.history_count > 0)
    {
        int last_index = command_history.history_count - 1;
        if (strcmp(command_history.history[last_index], command_history.history[last_index - 1]) != 0)
        {
            fprintf(file, "%s\n", command_history.history[last_index]);
        }
    }
    else
    {
        fprintf(file, "%s\n", command_history.history[0]);
    }

    fclose(file);
}

void load_command_history_from_file()
{
    FILE *file = fopen(HISTORY_FILE, "r");
    if (file != NULL)
    {
        char line[1000];
        while (fgets(line, sizeof(line), file) != NULL && command_history.history_count < MAX_HISTORY_SIZE)
        {
            // Remove newline character if present
            size_t length = strlen(line);
            if (line[length - 1] == '\n')
            {
                line[length - 1] = '\0';
            }

            strcpy(command_history.history[command_history.history_count], line);
            command_history.history_count++;
            command_history.current_index = command_history.history_count;
        }
        fclose(file);
    }
    else
    {
        // Create the history file if it doesn't exist
        file = fopen(HISTORY_FILE, "w");
        if (file != NULL)
        {
            fclose(file);
        }
        else
        {
            perror("Error creating history file");
        }
    }
}

void reset_current_index()
{
    command_history.current_index = command_history.history_count;
}
