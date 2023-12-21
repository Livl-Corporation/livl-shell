#include "main.h"

int main() {
    while (1) {
        print_prompt();

        // Read the input
        char* input = read_input();
        if (input == NULL) {
            return EXIT_FAILURE;
        }

        preprocess_input(input);

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
    }

    return EXIT_SUCCESS;
}
