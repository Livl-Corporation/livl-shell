#include "input_parser.h"

void preprocess_input(char* input) {
    char* operators[] = {"&&", "||", ">", "<", "&", ";"};
    int num_operators = sizeof(operators) / sizeof(char*);
    char* new_input = malloc(strlen(input) * 2 + 1); // Allocate enough space for the new input
    int j = 0;

    // Iterate over the input and add spaces around the operators
    for (int i = 0; i < strlen(input); i++) {
        int found = 0;

        // Check if the current character is an operator
        for (int k = 0; k < num_operators; k++) {
            // strncmp compares the first n characters of two strings
            if (strncmp(&input[i], operators[k], strlen(operators[k])) == 0) {
                new_input[j++] = ' ';
                strncpy(&new_input[j], &input[i], strlen(operators[k]));
                j += strlen(operators[k]);
                new_input[j++] = ' ';
                i += strlen(operators[k]) - 1;
                found = 1;
                break;
            }
        }
        if (!found) {
            new_input[j++] = input[i];
        }
    }
    new_input[j] = '\0';
    strcpy(input, new_input);
    free(new_input);
}

int is_operator(char *token) {
    char* operators[] = {"&&", "||", ">", "<", "&", ";"};
    int num_operators = sizeof(operators) / sizeof(char*);

    for (int i = 0; i < num_operators; i++) {
        if (strcmp(token, operators[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void process_token(char *token, char **commands, char **operators, char **currentCommand, int *cmdIndex, int *opIndex) {
    if (is_operator(token)) {
        operators[(*opIndex)++] = strdup(token);
    } else {
        if (*currentCommand == NULL) {
            *currentCommand = strdup(token);
        } else {
            size_t len = strlen(*currentCommand) + strlen(token) + 2;
            *currentCommand = realloc(*currentCommand, len);
            strcat(*currentCommand, " ");
            strcat(*currentCommand, token);
        }
    }
}

void store_command(char **commands, char **currentCommand, int *cmdIndex) {
    if (*currentCommand != NULL) {
        commands[(*cmdIndex)++] = *currentCommand;
        *currentCommand = NULL;
    }
}