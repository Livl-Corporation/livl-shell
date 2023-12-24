/**
 * @file redirection.h
 * @author Julien & Franck
 * @date 24 Dec 2023
 * @brief File containing the redirection functions to manage the redirection operators such as '<', '<<', '>', '>>' and '|'.
 */
#ifndef REDIRECTION_H
#define REDIRECTION_H

#include "typedef.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

/**
 * @brief Handles input redirection with '<' operator with '<<' operator
 * @param command Command to be check for input redirection
 * @return void
*/
void handle_input_redirection(const Command *command);

/**
 * @brief Handles output redirection with '>' operator with '>>' operator
 * @param command Command to be check for output redirection
 * @return void
*/
void handle_output_redirection(const Command *command);

/**
 * @brief Evaluate if a command sequence contains stream redirection operators
 * @param sequence: The command sequence to evaluate
*/
void evaluate_redirection(CommandSequence *sequence);

/**
 * @brief Execute a command with pipe operator
 * @param cmd1: The first command
 * @param cmd2: The second command
 * @return void
*/
void execute_pipe(Command *cmd1, Command *cmd2);

/**
 * @brief Evaluate if a command is a stream redirection command
 * @param command: The command to evaluate
*/
int is_redirection_command(const Command *command);

#endif //REDIRECTION_H
