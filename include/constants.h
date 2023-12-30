/**
 * @file constants.h
 * @author Julien & Franck
 * @date 29 Dec 2023
 * @brief Header file defining constants
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

// Maximums

/*!
 * \brief Maximum nmber of background processes
 */
#define MAX_BACKGROUND_PROCESSES 100

/**
 * @brief The max length of the input string
 */
#define MAX_INPUT_LENGTH 1024

/**
 * @brief The maximum number of commands in a command sequence
 */
#define MAX_COMMANDS 3

/**
 * @brief The maximum number of operators in a command sequence
 */
#define MAX_OPERATORS (MAX_COMMANDS - 1)

// Built-in commands

/**
 * @brief The status value to return when a built-in command is run successfully
 */
#define IS_BUILTIN_COMMAND 0

/**
 * @brief The status value to return when a command is not a built-in command
 */
#define IS_NOT_BUILTIN_COMMAND -1

// Colors

/**
 * @brief The YELB color
 */
#define YELB "\e[43m"

/**
 * @brief The RESET color (default color)
 */
#define RESET "\e[0m"

/**
 * @brief The RED color
 */
#define BLUE "\e[1;34m"

/**
 * @brief The RED color
 */
#define GREEN "\e[1;32m"

/**
 * @brief The RED color
 */
#define YELLOW "\e[1;33m"

// History

/**
 * @brief The max size of the history
 */
#define MAX_HISTORY_SIZE 1000

/**
 * @brief The history file name
 */
#define HISTORY_FILE "history.txt"

// Scheduler

/**
 * @brief The child process id (pid)
 */
#define CHILD_PROCESS 0

#endif // CONSTANTS_H