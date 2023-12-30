/**
 * @file utils.h
 * @author Julien & Franck
 * @date 30 Dec 2023
 * @brief File containing some utilities
 */

#ifndef UTILS_H
#define UTILS_H

#include <string.h>
#include <ctype.h>

/**
 * @brief Handle quotes in a string (remove them)
 * @param token: the string to handle
 */
void handle_quotes(char *token);

/**
 * @brief Remove the spaces at the beginning and the end of a string
 * @param str: the string to trim
 * @return the trimmed string
 */
char *trim(char *str);

#endif // UTILS_H