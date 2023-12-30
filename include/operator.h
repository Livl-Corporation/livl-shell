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
 * @brief Gets the type of the given operator
 * @param operator_str The operator string
 * @return The type of the operator
 */
OperatorType get_operator_type(const char *operator_str);

/**
 * @brief Gets the string corresponding to the given operator
 * @param operator_type The operator type
 * @return The string corresponding to the operator
 */
const char *get_operator_string(OperatorType operator_type);

#endif // OPERATOR_H
