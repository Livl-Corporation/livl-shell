/**
 * @file history_command.h
 * @author Julien & Franck
 * @date 24 Dec 2023
 * @brief File containing the functions to manage (load & save, etc.) the history of commands entered by the user to a file.
 */
#ifndef HISTORY_COMMAND_H
#define HISTORY_COMMAND_H

#include <stdio.h>
#include <stdlib.h>
#include "typedef.h"
#include <string.h>
#include "constants.h"

/**
 * @brief Initialize the global command history
 */
void init_command_history();

/**
 * @brief Add a command to the global command history
 * @param command The command to be added
 */
void add_to_command_history(const char *command);

/**
 * @brief Get the previous command from the global command history
 * @return The previous command
 */
void get_previous_command(char *input);

/**
 * @brief Get the next command from the global command history
 * @return The next command
 */
void get_next_command(char *input);

/**
 * @brief Save the command history to the history file
 */
void save_command_history_to_file();

/**
 * @brief Load the command history from the history file
 */
void load_command_history_from_file();

/**
 * @brief Reset current index to the end of the history
 */
void reset_current_index();

/**
 * @brief Free the global command history
 */
void free_command_history();

#endif // HISTORY_COMMAND_H
