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
int get_alias(char *name, char *command);

char *trim(char *str);

#endif // ALIAS_H