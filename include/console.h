#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdio.h>
#include <stdarg.h>

#define YELB "\e[43m"
#define RESET "\e[0m"
#define BLUE "\e[1;34m"

/**
 * @brief Print the title of the program
*/
void print_title();

/**
 * @brief Print the prompt
*/
void print_info(const char *text, ...);

#endif //CONSOLE_H
