#include "main.h"

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