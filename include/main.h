/**
 * @file main.h
 * @author Julien & Franck
 * @date 24 Dec 2023
 * @brief File containing the main header file to include all the other header files.
 */
#ifndef MAIN_H
#define MAIN_H

#include "console.h"
#include "input_parser.h"
#include "command_sequence.h"
#include "history_command.h"
#include "alias.h"
#include "builtin_commands.h"

/**
 * @brief Run the shell in batch mode.
 * @param argv The arguments of the shell.
 * @param argc The number of arguments.
 */
void run_batch_mode(char *argv[], int argc);

/**
 * @brief Run the shell in interactive mode.
 */
void run_interactive_mode();

/**
 * @brief Handle the input.
 * @param input The input to handle.
 */
void handle_input(char *input);

#endif // MAIN_H
