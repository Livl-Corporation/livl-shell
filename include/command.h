/**
 * @file command.h
 * @author Julien & Franck
 * @date 24 Dec 2023
 * @brief File containing the command functions to manage the commands entered by the user (parsing, evaluation, etc.).
 */
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
 * @brief Handle quotes in a string (remove them)
 * @param token: the string to handle
*/
void handle_quotes(char **token);

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
 * @brief Initialize a command
 * @param cmd: the command to initialize
*/
void initializeCommand(Command *cmd);

/**
 * @brief Get the complete command (command + arguments) as a string
 * @param cmd: the command to get
 * @return the complete command
*/
char* get_complete_command(const Command *cmd);

#endif //COMMAND_H
