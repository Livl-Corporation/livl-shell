#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <stddef.h>

/**
 * Structur that represents a command
 * @param command: the command name
 * @param arguments: the command arguments
 * @param complete_command: the complete command (command + arguments)
 * @param num_arguments: the number of arguments
*/
typedef struct {
    char *command;   
    char **arguments;
    char **complete_command;
    int num_arguments;
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

#endif //TYPEDEF_H
