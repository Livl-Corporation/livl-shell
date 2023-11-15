#ifndef COMMAND_H
#define COMMAND_H

#include "typedef.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Evaluate a command from a string
 * @param input: the string to evaluate
 * @return the command structure
*/
Command evaluateCommand(const char *input);

/**
 * Free a command
 * @param cmd: the command to free
*/
void freeCommand(Command *cmd);

/**
 * Print a command
 * @param cmd: the command to print
*/
void printCommand(Command *cmd);

/**
 * Get the complete command (command + arguments) as a string 
 * It is useful for execvp(const char* command, char* argv[])
 * @param cmd: the command to get
 * @return the complete command
*/
char** getCompleteCommand(Command *cmd);

#endif //COMMAND_H
