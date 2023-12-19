#include "main.h"

void preprocess_input(char* input) {
    char* operators[] = {"&&", "||", ">", "<", "&", ";"};
    int num_operators = sizeof(operators) / sizeof(char*);

    for (int i = 0; i < num_operators; i++) {
        char* pos = input;
        // Replace all operators with a space before and after
        while ((pos = strstr(pos, operators[i])) != NULL) {
            memmove(pos + strlen(operators[i]), pos, strlen(pos) + 1);
            for (int j = 0; j < strlen(operators[i]); j++) {
                pos[j] = ' ';
            }
            pos += strlen(operators[i]) + 1;
        }
    }

    // Handle single character operators separately
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == '>' || input[i] == '<' || input[i] == '&' || input[i] == ';') {
            memmove(&input[i+1], &input[i], strlen(input) - i + 1);
            input[i] = ' ';
            input[i+2] = ' ';
            i += 2;
        }
    }
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

int main() {
    print_title();

    char input[MAX_INPUT_LENGTH];

    printf(">livl-shell$ ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    preprocess_input(input);

    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    char *token;
    char *commands[MAX_COMMANDS];
    char *operators[MAX_COMMANDS - 1];

    token = strtok(input, " \n");

    int cmdIndex = 0;
    int opIndex = 0;
    char *currentCommand = NULL;

    CommandSequence sequence;
    sequence.commands = malloc(MAX_COMMANDS * sizeof(Command));
    sequence.operators = malloc((MAX_COMMANDS - 1) * sizeof(char *));
    sequence.num_commands = 0;

    while (token != NULL) {
        process_token(token, commands, operators, &currentCommand, &cmdIndex, &opIndex);

        token = strtok(NULL, " \n");

        if (token == NULL || is_operator(token)) {
            store_command(commands, &currentCommand, &cmdIndex);
        }
    }

    for (int i = 0; i < cmdIndex; i++) {
        sequence.commands[sequence.num_commands++] = evaluateCommand(commands[i]);
        free(commands[i]);
    }

    for (int i = 0; i < opIndex; i++) {
        sequence.operators[i] = strdup(operators[i]);
        printf(" * Operator: %s\n", sequence.operators[i]);
        free(operators[i]);
    }

    int result = executeCommandSequence(&sequence);

    if (result < 0) {
        fprintf(stderr, "An error occurred while executing the commands\n");
    }

    freeCommandSequence(&sequence);

    return EXIT_SUCCESS;
}