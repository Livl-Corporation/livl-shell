#include "command_sequence.h"

void command_sequence_init(char *input) {
    const char *delimeters = " \n";
    
    char *commands[MAX_COMMANDS];
    char *operators[MAX_OPERATORS];

    int command_count = 0;
    int operator_count = 0;
    char *currentCommand = NULL;

    CommandSequence sequence;
    sequence.commands = malloc(MAX_COMMANDS * sizeof(Command));
    sequence.operators = malloc(MAX_OPERATORS * sizeof(char *));
    sequence.num_commands = 0;

    char *token = strtok(input, delimeters);
    while (token != NULL) {
        process_token(token, commands, operators, &currentCommand, &command_count, &operator_count);
        token = strtok(NULL, delimeters);

        if (token == NULL || is_operator(token)) {
            store_command(commands, &currentCommand, &command_count);
        }
    }

    // Build the command sequence with its commands
    for (int i = 0; i < command_count; i++) {
        sequence.commands[sequence.num_commands++] = evaluateCommand(commands[i]);
        free(commands[i]);
    }

    // Build the command sequence with its operators
    for (int i = 0; i < operator_count; i++) {
        sequence.operators[i] = strdup(operators[i]);
        printf(" * Operator: %s\n", sequence.operators[i]);
        free(operators[i]);
    }

    evaluate_redirection(&sequence);

    int result = executeCommandSequence(&sequence);

    if (result < 0) {
        fprintf(stderr, "An error occurred while executing the commands\n");
    }

    free_command_sequence(&sequence);
}


void process_token(char *token, char **commands, char **operators, char **currentCommand, int *cmdIndex, int *opIndex) {
    if (is_operator(token)) {
        operators[(*opIndex)++] = strdup(token);
        return;
    } 
    
    // Token is a command
    if (*currentCommand == NULL) {
        *currentCommand = strdup(token);
    } else {
        size_t len = strlen(*currentCommand) + strlen(token) + 2;
        char* temp = realloc(*currentCommand, len);
        if (temp == NULL) {
            fprintf(stderr, "Error reallocating memory\n");
            return;
        }
        *currentCommand = temp;
        strcat(*currentCommand, " ");
        strcat(*currentCommand, token);
    }
    
}

void store_command(char **commands, char **currentCommand, int *cmdIndex) {
    if (*currentCommand != NULL) {
        commands[(*cmdIndex)++] = *currentCommand;
        *currentCommand = NULL;
    }
}

void free_command_sequence(CommandSequence *sequence) {
    for (int i = 0; i < sequence->num_commands; ++i) {
        freeCommand(&sequence->commands[i]);
    }
    free(sequence->commands);
}