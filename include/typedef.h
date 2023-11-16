#ifndef TYPEDEF
#define TYPEDEF

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


// Define a structure to represent a sequence of commands and operators
typedef struct {
    Command *commands;      // Array of commands
    char **operators;       // Array of operators
    size_t num_commands;    // Number of commands
} CommandSequence;

#endif //TYPEDEF
