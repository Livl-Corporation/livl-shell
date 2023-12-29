/**
 * @file scheduler.h
 * @author Julien & Franck
 * @date 24 Dec 2023
 * @brief File containing the scheduler functions to manage the execution of commands.
 */
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
#include "constants.h"

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
int execute_command_sequence(const CommandSequence *sequence);

#endif // SCHEDULER_H