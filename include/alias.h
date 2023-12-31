/**
 * @file alias.h
 * @author Julien & Franck
 * @date 30 Dec 2023
 * @brief Managing livl-shell aliases
 */
#ifndef ALIAS_H
#define ALIAS_H

#include "constants.h"
#include "typedef.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "utils.h"

/**
 * @brief Initialize aliases from file
 */
void init_aliases();

/**
 * @brief Try to get an alias for a given name
 * @param name The name of the alias
 * @param command The string will be filled with the alias command if exist
 * @return 0 if no alias found, 1 otherwise
 */
int is_alias(const char *name, char *command);

/**
 * @brief Free aliases
 */
void free_aliases();

/**
 * @brief Parse the input to replace aliases
 * @param input The input string
 */
void parse_aliases(char *input);

#endif // ALIAS_H