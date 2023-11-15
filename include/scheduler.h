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

int executeCommand(const Command *cmd);

/**
 * @brief Executes a command
 * @param cmd1 The command to execute
 * @param cmd2 The second to execute
 * @param control_operator The control operator
 * @return 0 if success, -1 if error
 * 
*/
int executeCommands(const Command *cmd1, const Command *cmd2, const char *control_operator);

/**
 * @brief Prints a command
 * @param cmd The command to print
*/
void printCommand(Command *cmd);

#endif //SCHEDULER_H
