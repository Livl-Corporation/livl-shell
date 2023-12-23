#ifndef BACKGROUND_MANAGER_H
#define BACKGROUND_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "typedef.h"
#include "command.h"

/**
 * @brief Variable that represents the number of background processes
*/
#define MAX_BACKGROUND_PROCESSES 100

/**
 * @brief Method that checks if a background process has completed so it prints to the user the corresponding jobs terminated
*/
void check_completed_background_processes();

/**
 * @brief Add background process to store information about the background process
 * @param pid : the pid of the process
 * @param command : the command executed
*/
void add_background_process(pid_t pid, const Command *command);

#endif //BACKGROUND_MANAGER_H
