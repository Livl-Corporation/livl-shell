#ifndef TYPEDEF
#define TYPEDEF

/**
 * Structur that represents a command
 * @param command: the command name
 * @param arguments: the command arguments
 * @param num_arguments: the number of arguments
*/
typedef struct {
    char *command;   
    char **arguments;
    int num_arguments;
} Command;

#endif //TYPEDEF
