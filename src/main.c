#include "main.h"

#include "main.h"

void preprocess_input(char* input) {
    char* operators[] = {"&&", "||", ">", "<", "&", ";"};
    int num_operators = sizeof(operators) / sizeof(char*);

    for (int i = 0; i < num_operators; i++) {
        char* pos = input;
        while ((pos = strstr(pos, operators[i])) != NULL) {
            memmove(pos + 1, pos, strlen(pos) + 1);
            *pos = ' ';
            pos += 3;
            memmove(pos + 1, pos, strlen(pos) + 1);
            *pos = ' ';
        }
    }
}


int main() {

    print_title();

    char input[MAX_INPUT_LENGTH];

    printf(">livl-shell$ ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    // Preprocess the input
    preprocess_input(input);

    // Remove newline character if present
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    char *token;
    char *commands[MAX_COMMANDS];
    char *operators[MAX_COMMANDS - 1];

    // Tokenize the input based on spaces
    token = strtok(input, " \n");

    int cmdIndex = 0;
    int opIndex = 0;
    char *currentCommand = NULL;

    CommandSequence sequence;
    sequence.commands = malloc(MAX_COMMANDS * sizeof(Command));
    sequence.operators = malloc((MAX_COMMANDS - 1) * sizeof(char *));
    sequence.num_commands = 0;

    while (token != NULL) {
        if (strcmp(token, "&&") == 0 || strcmp(token, "||") == 0 || strcmp(token, ">") == 0 ||
            strcmp(token, "<") == 0 || strcmp(token, "&") == 0 || strcmp(token, ";") == 0) {
            // It's an operator
            operators[opIndex++] = strdup(token);
        } else {
            // It's part of a command
            if (currentCommand == NULL) {
                currentCommand = strdup(token);
            } else {
                size_t len = strlen(currentCommand) + strlen(token) + 2;
                currentCommand = realloc(currentCommand, len);
                strcat(currentCommand, " ");
                strcat(currentCommand, token);
            }
        }

        // Move to the next token
        token = strtok(NULL, " \n");

        // If an operator is encountered or we reach the end, store the current command
        if (token == NULL || strcmp(token, "&&") == 0 || strcmp(token, "||") == 0 ||
            strcmp(token, ">") == 0 || strcmp(token, "<") == 0 || strcmp(token, "&") == 0 || strcmp(token, ";") == 0) {
            if (currentCommand != NULL) {
                commands[cmdIndex++] = currentCommand;
                currentCommand = NULL;
            }
        }
    }

    // Populate the CommandSequence structure
    for (int i = 0; i < cmdIndex; i++) {
        sequence.commands[sequence.num_commands++] = evaluateCommand(commands[i]);
        free(commands[i]);
    }

    for (int i = 0; i < opIndex; i++) {
        sequence.operators[i] = strdup(operators[i]);
        free(operators[i]);
    }

    // Execute the command sequence
    int result = executeCommandSequence(&sequence);

    if (result < 0) {
        fprintf(stderr, "An error occurred while executing the commands\n");
    }

    // Free the memory
    freeCommandSequence(&sequence);

    return EXIT_SUCCESS;
}