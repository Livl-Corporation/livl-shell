#ifndef TYPEDEF
#define TYPEDEF

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

#endif //TYPEDEF
