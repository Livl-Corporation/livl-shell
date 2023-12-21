#ifndef COMMAND_SEQUENCE_H
#define COMMAND_SEQUENCE_H

#include "command.h"
#include "scheduler.h"
#include "operator.h"

#define MAX_COMMANDS 3
#define MAX_OPERATORS 2

/**
 * @brief Initialize the command sequence module.
 * @param input The input string parsed
*/
void command_sequence_init(char *input);

/**
 * @brief Checks if the given token is a command or an operator
 * @param token The token to be checked
*/
void process_token(char *token, char **commands, char **operators, char **currentCommand, int *cmdIndex, int *opIndex);

/**
 * @brief Stores the current command in the commands array
 * @param commands The array of commands
 * @param currentCommand The current command
 * @param cmdIndex The index of the current command
*/
void store_command(char **commands, char **currentCommand, int *cmdIndex);

#endif //COMMAND_SEQUENCE_H
