#ifndef BUILTIN_COMMANDS_H
#define BUILTIN_COMMANDS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "typedef.h"

#define IS_BUILTIN_COMMAND 0
#define IS_NOT_BUILTIN_COMMAND -1

/**
 * @brief Executes a command
 * @param command The command to execute
 * @return The status of the execution (0 if success, -1 if not a built-in command, 1 if error)
*/
int execute_builtin_command(const Command *command);

/**
 * @brief Prints the current working directory
*/
void pwd();

/**
 * @brief Changes the current directory
 * @param path The path to the new directory
*/
void cd(char* path);

/**
 * @brief Exits the shell
*/
void exit_shell();

/**
 * @brief Prints a message
 * @param command The command to execute to be able to print all the arguments
*/
void echo(const Command *command);

#endif //BUILTIN_COMMANDS_H
