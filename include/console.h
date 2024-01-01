/**
 * @file console.h
 * @author Julien & Franck
 * @date 24 Dec 2023
 * @brief File containing the console functions to manage the console (print information, etc.) to avoid code duplication.
 */
#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include "constants.h"

/**
 * @brief Generic print information to the console
 * @param text The text to be printed
 * @param ... optional arguments like %s, %d, etc.
 */
void print_info(const char *text, ...);

/**
 * @brief Print the prompt to the console (username @ hostname:$)
 */
void print_prompt();

/**
 * @brief Print the error to the console
 * @param format The format of the error
 * @param ... optional arguments like %s, %d, etc.
 */
void print_perror(const char *format, ...);

#endif // CONSOLE_H
