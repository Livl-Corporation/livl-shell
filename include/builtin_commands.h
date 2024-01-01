/**
 * @file builtin_commands.h
 * @author Julien & Franck
 * @date 24 Dec 2023
 * @brief File containing the built-in commands functions to manage the built-in commands such as cd, pwd, echo, exit.
 */
#ifndef BUILTIN_COMMANDS_H
#define BUILTIN_COMMANDS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "typedef.h"
#include "constants.h"
#include "command_sequence.h"

/**
 * @brief Executes a command
 * @param command The command to execute
 * @param sequence The command sequence to free
 * @return The status of the execution (0 if success, -1 if not a built-in command, 1 if error)
 */
int execute_builtin_command(const Command *command, CommandSequence *sequence);

/**
 * @brief Prints the current working directory
 */
void pwd();

/**
 * @brief Changes the current directory
 * @param path The path to the new directory
 */
void cd(const char *path);

/**
 * @brief Checks if the command is a built-in command
 * @param command The command to check
 * @param expected The expected command name
 * @return 1 if the command is a built-in command, 0 if not
 */
int is_builtin_command(const Command *command, const char *expected);

/**
 * @brief Exits the shell
 * 
 * @param sequence The command sequence to free
 */
void exit_shell(CommandSequence *sequence);

/**
 * @brief Prints a message
 * @param command The command to execute to be able to print all the arguments
 */
void echo(const Command *command);

#endif // BUILTIN_COMMANDS_H
