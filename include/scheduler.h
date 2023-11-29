#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "typedef.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "command.h"

#define CHILD_PROCESS 0

/**
 * @brief Executes a command
 * @param cmd The command to execute
 * @return The status of the execution
*/
int executeCommand(const Command *cmd);

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
