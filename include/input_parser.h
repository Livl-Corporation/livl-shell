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

#define MAX_INPUT_LENGTH 1024

/**
 * @brief Reads the input from the console
 * @return The input string
*/
char* read_input();

/**
 * @brief Checks if the input string is all whitespace
 * @param input The input string
 * @return 1 if the input string is all whitespace, 0 otherwise
*/
int is_all_whitespace(const char* input);

/**
 * @brief Parses the input string into commands and operators
 * @param input The input string to be parsed
*/
void preprocess_input(char* input);

#endif //INPUT_PARSER_H
