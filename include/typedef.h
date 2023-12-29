/**
 * @file typedef.h
 * @author Julien & Franck
 * @date 24 Dec 2023
 * @brief File containing all the typedefs used in the shell program.
 */
#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <stddef.h>
#include <sys/types.h>
#include "constants.h"

/**
 * Enum that represents the type of an operator
 */
typedef enum
{
    AND,
    OR,
    REDIRECTION_APPEND_OUTPUT,
    REDIRECTION_APPEND_INPUT,
    SEMICOLON,
    PIPE,
    BACKGROUND,
    REDIRECTION_OUTPUT,
    REDIRECTION_INPUT,
    UNKNOWN,
} OperatorType;

/**
 * @struct BackgroundProcess
 * @brief Struct that represents a background process.
 *
 * @var BackgroundProcess::pid
 * Process ID.
 *
 * @var BackgroundProcess::job_number
 * Job number.
 *
 * @var BackgroundProcess::command
 * Command and its arguments.
 */
typedef struct
{
    pid_t pid;
    int job_number;
    char *command;
} BackgroundProcess;

/**
 * @struct Redirection
 * @brief Struct that represents a redirection.
 *
 * @var Redirection::input_file
 * Input file.
 *
 * @var Redirection::output_file
 * Output file.
 *
 * @var Redirection::append_input
 * Append input.
 *
 * @var Redirection::append_output
 * Append output.
 */
typedef struct
{
    char *input_file;
    char *output_file;
    int append_input;
    int append_output;
} Redirection;

/**
 * @struct Command
 * @brief Struct that represents a command.
 *
 * @var Command::command
 * Command.
 *
 * @var Command::arguments
 * Arguments.
 *
 * @var Command::complete_command
 * Complete command.
 *
 * @var Command::num_arguments
 * Number of arguments.
 *
 * @var Command::redirection
 * Redirection.
 */
typedef struct
{
    char *command;
    char **arguments;
    char **complete_command;
    int num_arguments;
    Redirection redirection;
} Command;

/**
 * @struct CommandSequence
 * @brief Struct that represents a command sequence.
 *
 * @var CommandSequence::commands
 * Array of commands.
 *
 * @var CommandSequence::operators
 * Array of operators.
 *
 * @var CommandSequence::num_commands
 * Number of commands.
 */
typedef struct
{
    Command *commands;   // Array of commands
    char **operators;    // Array of operators
    size_t num_commands; // Number of commands
} CommandSequence;

/**
 * @struct CommandHistory
 * @brief Struct that represents the command history.
 *
 * @var CommandHistory::history
 * Array of commands.
 *
 * @var CommandHistory::history_count
 * Number of commands in the history.
 *
 * @var CommandHistory::current_index
 * Current index in the history.
 */
typedef struct
{
    char history[MAX_HISTORY_SIZE][MAX_INPUT_LENGTH];
    int history_count;
    int current_index;
} CommandHistory;

#endif // TYPEDEF_H
