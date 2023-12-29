/**
 * @file background_manager.h
 * @author Julien & Franck
 * @date 24 Dec 2023
 * @brief File containing the background manager functions to manage the background processes.
 */
#ifndef BACKGROUND_MANAGER_H
#define BACKGROUND_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "typedef.h"
#include "command.h"
#include "constants.h"

/*!
 * \brief Method that checks if a background process has completed
 *        and prints corresponding information to the user.
 */
void check_completed_background_processes();

/*!
 * \brief Add background process to store information about the process.
 * \param pid : the pid of the process
 * \param command : the command executed
 */
void add_background_process(pid_t pid, const Command *command);

#endif // BACKGROUND_MANAGER_H
