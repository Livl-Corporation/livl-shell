#include "input_parser.h"
#include "history_command.h"
#include "input_parser.h"
#include "history_command.h"

char* read_input() {
    char* input = malloc(MAX_INPUT_LENGTH * sizeof(char));
    if (input == NULL) {
        fprintf(stderr, "Error allocating memory for input\n");
        return NULL;
    }

    if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return NULL;
    }

    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    return input;
}

int is_all_whitespace(const char* input) {
    for (int i = 0; i < strlen(input); i++) {
        if (!isspace(input[i])) {
            return 0;
        }
    }
    return 1;
}

void preprocess_input(char* input) {
    char* new_input = malloc(strlen(input) * 2 + 1); // Allocate enough space for the new input

    if (new_input == NULL) {
        fprintf(stderr, "Error allocating memory\n");
        return;
    }

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

