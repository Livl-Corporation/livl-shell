#ifndef REDIRECTION_H
#define REDIRECTION_H

#include "typedef.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

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
 * @brief Evaluate if a command is a stream redirection command
 * @param command: The command to evaluate
*/
int is_redirection_command(const Command *command);

#endif //REDIRECTION_H
