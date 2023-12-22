#ifndef COMMAND_H
#define COMMAND_H

#include "typedef.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Evaluate a command from a string
 * @param input: the string to evaluate
 * @return the command structure
*/
Command evaluateCommand(const char *input);

/**
 * @brief Evaluate if a command sequence contains stream redirection operators
 * @param sequence: The command sequence to evaluate
*/
void evaluateStreamRedirection(CommandSequence *sequence);

/**
 * @brief Free a command
 * @param cmd: the command to free
*/
void freeCommand(Command *cmd);

/**
 * @brief Print a command
 * @param cmd: the command to print
*/
void printCommand(Command *cmd);

/**
 * @brief Get the complete command (command + arguments) as a string 
 * @brief It is useful for execvp(const char* command, char* argv[])
 * @param cmd: the command to get
 * @return the complete command
*/
char** getCompleteCommand(Command *cmd);

/**
 * Free the memory allocated for a command sequence
 * Each command in the sequence is also freed
 * @param sequence: the command sequence to free
*/
void freeCommandSequence(CommandSequence *sequence);

#endif //COMMAND_H
