#include "history_command.h"

CommandHistory global_command_history;

void init_command_history()
{
    global_command_history.history_count = 0;
    global_command_history.current_index = -1;
    load_command_history_from_file();
}

void add_to_command_history(const char *command)
{
    if (global_command_history.history_count < MAX_HISTORY_SIZE)
    {
        strcpy(global_command_history.history[global_command_history.history_count], command);
        global_command_history.history_count++;
        global_command_history.current_index = global_command_history.history_count;
        save_command_history_to_file();
    }
    else
    {
        printf("History is full. Delete your history.txt file.\n");
    }
}

const char *get_previous_command()
{
    if (global_command_history.current_index > 0)
    {
        global_command_history.current_index--;
        return global_command_history.history[global_command_history.current_index];
    }
    else
    { // Already at the earliest command
        return NULL;
    }
}

const char *get_next_command()
{
    if (global_command_history.current_index < global_command_history.history_count - 1)
    {
        global_command_history.current_index++;
        return global_command_history.history[global_command_history.current_index];
    }
    else
    { // Already at the latest command
        return NULL;
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
    if (global_command_history.history_count > 0)
    {
        int last_index = global_command_history.history_count - 1;
        if (strcmp(global_command_history.history[last_index], global_command_history.history[last_index - 1]) != 0)
        {
            fprintf(file, "%s\n", global_command_history.history[last_index]);
        }
    }
    else
    {
        fprintf(file, "%s\n", global_command_history.history[0]);
    }

    fclose(file);
}

void load_command_history_from_file()
{
    FILE *file = fopen(HISTORY_FILE, "r");
    if (file != NULL)
    {
        char line[1000];
        while (fgets(line, sizeof(line), file) != NULL && global_command_history.history_count < MAX_HISTORY_SIZE)
        {
            // Remove newline character if present
            size_t length = strlen(line);
            if (line[length - 1] == '\n')
            {
                line[length - 1] = '\0';
            }

            strcpy(global_command_history.history[global_command_history.history_count], line);
            global_command_history.history_count++;
            global_command_history.current_index = global_command_history.history_count;
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
