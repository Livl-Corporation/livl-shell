/**
 * @file operator.h
 * @author Julien & Franck
 * @date 24 Dec 2023
 * @brief File containing the operator functions to manage the operators that can be used in the shell.
 */
#ifndef OPERATOR_H
#define OPERATOR_H

#include <string.h> 
#include "typedef.h"

/**
 * The list of operators that can be used
*/
extern const char *operators[];

/**
 * The number of operators that can be used
*/
extern const int num_operators;

/**
 * @brief Checks if the given token is an operator
 * @param token The token to be checked
 * @return 1 if the token is an operator, 0 otherwise
*/
int is_operator(const char *token);

/**
 * @brief Gets the type of the given operator
 * @param operator_str The operator string
 * @return The type of the operator
*/
OperatorType get_operator_type(const char *operator_str);

/**
 * @brief Gets the string representation of the given operator
 * @param op The operator
 * @return The string representation of the operator
*/
const char *get_operator_string(OperatorType op);

#endif //OPERATOR_H
