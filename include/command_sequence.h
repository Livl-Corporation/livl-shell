/**
 * @file command_sequence.h
 * @author Julien & Franck
 * @date 24 Dec 2023
 * @brief File containing the command sequence functions to manage the command sequence (commands and operators).
 */
#ifndef COMMAND_SEQUENCE_H
#define COMMAND_SEQUENCE_H

#include "command.h"
#include "scheduler.h"
#include "operator.h"
#include "redirection.h"

/**
 * @brief The maximum number of commands in a command sequence
*/
#define MAX_COMMANDS 3

/**
 * @brief The maximum number of operators in a command sequence
*/
#define MAX_OPERATORS (MAX_COMMANDS - 1)

/**
 * @brief Initialize the command sequence module.
 * @param input The input string parsed
*/
void command_sequence_init(char *input);

/**
 * @brief Checks if the given token is a command or an operator
 * @param token The token to be checked
 * @param commands The array of commands
 * @param operators The array of operators
 * @param currentCommand The current command
 * @param cmdIndex The index of the current command
 * @param opIndex The index of the current operator
 * 
*/
void process_token(char *token, char **commands, char **operators, char **currentCommand, int *cmdIndex, int *opIndex);

/**
 * @brief Stores the current command in the commands array
 * @param commands The array of commands
 * @param currentCommand The current command
 * @param cmdIndex The index of the current command
*/
void store_command(char **commands, char **currentCommand, int *cmdIndex);

/**
 * Free the memory allocated for a command sequence
 * Each command in the sequence is also freed
 * @param sequence: the command sequence to free
*/
void free_command_sequence(CommandSequence *sequence);

#endif //COMMAND_SEQUENCE_H
