/**
 * @file input_parser.h
 * @author Julien & Franck
 * @date 24 Dec 2023
 * @brief File containing the input parser functions to manage the input entered by the user (parsing, evaluation, etc.).
 */
#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "operator.h"
#include <ctype.h>
#include "constants.h"
#include <termios.h>
#include <unistd.h>
#include "history_command.h"
#include "console.h"

/**
 * @brief Reads the input from the console
 * @return The input string
 */
char *read_input();

/**
 * @brief Checks if the input string is all whitespace
 * @param input The input string
 * @return 1 if the input string is all whitespace, 0 otherwise
 */
int is_all_whitespace(const char *input);

/**
 * @brief Parses the input string into commands and operators
 * @param input The input string to be parsed
 */
void preprocess_input(char *input);

/**
 * @brief Handle arrow up logic
 * @param input The input string
 * @param index The index of the cursor
 */
void handle_arrow_up(char *input, int *index);

/**
 * @brief Handle arrow down logic
 * @param input The input string
 * @param index The index of the cursor
 */
void handle_arrow_down(char *input, int *index);

/**
 * @brief Handle arrow left logic
 * @param input The input string
 * @param index The index of the cursor
 */
void handle_arrow_left(char *input, int *index);

/**
 * @brief Handle arrow right logic
 * @param input The input string
 * @param index The index of the cursor
 */
void handle_arrow_right(char *input, int *index);

/**
 * @brief Handle backspace logic
 * @param input The input string
 * @param index The index of the cursor
 */
void handle_backspace(char *input, int *index);

/**
 * @brief Replace input with the provided string
 * @param input The input string
 * @param index The index of the cursor
 */
void replace_input(char *input, int *index, const char *replacement);

#endif // INPUT_PARSER_H
