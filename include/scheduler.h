#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "typedef.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "command.h"
#include "console.h"
#include "builtin_commands.h"
#include "redirection.h"
#include "operator.h"
#include "background_manager.h"

/**
 * @brief The child process id (pid)
*/
#define CHILD_PROCESS 0

/**
 * @brief Executes a command
 * @param command The command to execute
 * @param run_in_background 0 for false, 1 for true
 * @return The status of the execution
*/
int execute_external_command(const Command *command, int run_in_background);

/**
 * @brief Executes a command
 * @param command The command to execute
 * @param run_in_background 0 for false, 1 for true
 * @return The status of the execution
*/
int execute_command(const Command *command, int run_in_background);

/**
 * @brief Executes a sequence of commands with operators
 * @param sequence The sequence of commands to execute
 * @return The status of the execution
*/
int executeCommandSequence(const CommandSequence *sequence);

/**
 * @brief Prints a command
 * @param cmd The command to print
*/
void printCommand(Command *cmd);

#endif //SCHEDULER_H