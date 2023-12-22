#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

#define YELB "\e[43m"
#define RESET "\e[0m"
#define BLUE "\e[1;34m"
#define GREEN "\e[1;32m"
#define YELLOW "\e[1;33m"

/**
 * @brief Print the title of the program
*/
void print_title();

/**
 * @brief Generic print information to the console
 * @param text The text to be printed
 * @param ... optional arguments like %s, %d, etc.
*/
void print_info(const char *text, ...);

/**
 * @brief Print the prompt to the console (username@hostname:$)
*/
void print_prompt();

/**
 * @brief Print the error to the console
 * @param format The format of the error
 * @param ... optional arguments like %s, %d, etc.
*/
void print_perror(const char *format, ...);

#endif //CONSOLE_H
