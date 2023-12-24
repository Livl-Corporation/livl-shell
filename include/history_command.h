#ifndef HISTORY_COMMAND_H
#define HISTORY_COMMAND_H

#include <stdio.h>
#include <stdlib.h>
#include "typedef.h"
#include <string.h>

#define MAX_HISTORY_SIZE 1000
#define HISTORY_FILE "history.txt"

/**
 * @brief The global history of commands entered by the user
*/
extern CommandHistory global_command_history;

/**
 * @brief Initialize the global command history
*/
void initialize_command_history();

/**
 * @brief Add a command to the global command history
 * @param command The command to be added
*/
void add_to_command_history(const char *command);

/**
 * @brief Get the previous command from the global command history
 * @return The previous command
*/
const char *get_previous_command();

/**
 * @brief Get the next command from the global command history
 * @return The next command
*/
const char *get_next_command();

/**
 * @brief Save the command history to the history file
*/
void save_command_history_to_file();

/**
 * @brief Load the command history from the history file
*/
void load_command_history_from_file();

#endif //HISTORY_COMMAND_H
