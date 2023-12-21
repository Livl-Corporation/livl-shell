#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// The list of operators that can be used
extern const char* operators[];

/**
 * @brief Parses the input string into commands and operators
 * @param input The input string to be parsed
*/
void preprocess_input(char* input);

/**
 * @brief Checks if the given token is an operator
 * @param token The token to be checked
 * @return 1 if the token is an operator, 0 otherwise
*/
int is_operator(char *token);

/**
 * @brief Checks if the given token is a command
 * @param token The token to be checked
 * @return 1 if the token is a command, 0 otherwise
*/
void process_token(char *token, char **commands, char **operators, char **currentCommand, int *cmdIndex, int *opIndex);

/**
 * @brief Stores the current command in the commands array
 * @param commands The array of commands
 * @param currentCommand The current command
 * @param cmdIndex The index of the current command
*/
void store_command(char **commands, char **currentCommand, int *cmdIndex);

#endif //INPUT_PARSER_H
