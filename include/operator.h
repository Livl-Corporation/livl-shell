#ifndef OPERATOR_H
#define OPERATOR_H

#include <string.h> 

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

#endif //OPERATOR_H
