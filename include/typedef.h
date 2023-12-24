#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <stddef.h>
#include <sys/types.h>

/**
 * Enum that represents the type of an operator
*/
typedef enum {
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
 * Structur that represents a background process
 * @param pid: the process id
 * @param job_number: the job number
 * @param command: the command and its arguments
*/
typedef struct {
    pid_t pid;
    int job_number;
    char *command;
} BackgroundProcess;

/**
 * Structur that represents a redirection
 * @param input_file: the input file (a file that will be read)
 * @param output_file: the output file (a file that will be written)
 * @param append_input: 0 for false, 1 for true (<<)
 * @param append_output: 0 for false, 1 for true (>>)
*/
typedef struct {
    char *input_file;
    char *output_file;
    int append_input;
    int append_output;
} Redirection;

/**
 * Structur that represents a command
 * @param command: the command name
 * @param arguments: the command arguments
 * @param complete_command: the complete command (command + arguments)
 * @param num_arguments: the number of arguments
 * @param redirection: the redirection (input and output files)
*/
typedef struct {
    char *command;   
    char **arguments;
    char **complete_command;
    int num_arguments;
    Redirection redirection;
} Command;

/**
 * Structur that represents a command sequence
 * @param commands: the commands
 * @param operators: the operators between commands
 * @param num_commands: the number of commands
*/
typedef struct {
    Command *commands;      // Array of commands
    char **operators;       // Array of operators
    size_t num_commands;    // Number of commands
} CommandSequence;

/**
 * Structur that represents a command history
 * @param history: the history of commands
 * @param history_count: the number of commands in the history
 * @param current_index: the current index in the history
*/
typedef struct {
    char history[1000][1000];
    int history_count;
    int current_index;
} CommandHistory;

#endif //TYPEDEF_H
