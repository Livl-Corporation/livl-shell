#include "input_parser.h"

char* read_input(char *input) {
    if (input == NULL)
    {
        perror("input is not allocated");
        return NULL;
    }

    if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
        perror("fgets");
        free(input);
        return NULL;
    }

    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    return input;
}

int is_all_whitespace(const char *input)
{
    for (int i = 0; i < strlen(input); i++)
    {
        if (!isspace(input[i]))
        {
            return 0;
        }
    }
    return 1;
}

void preprocess_input(char *input)
{
    char *new_input = malloc(strlen(input) * 2 + 1); // Allocate enough space for the new input

    if (new_input == NULL)
    {
        perror("malloc");
        return;
    }

    int j = 0;

    // Iterate over the input and add spaces around the operators
    for (int i = 0; i < strlen(input); i++)
    {

        char token[2] = {input[i], input[i + 1]};
        OperatorType operator_type = get_operator_type(token);

        if (operator_type != UNKNOWN)
        {

            const char *operator_string = get_operator_string(operator_type);
            int operator_length = strlen(get_operator_string(operator_type));

            new_input[j++] = ' ';
            strncpy(&new_input[j], operator_string, operator_length);
            j += operator_length;
            new_input[j++] = ' ';
            i += operator_length - 1;
            continue;
        }
        else
        {
            new_input[j++] = input[i];
        }
    }
    new_input[j] = '\0';
    strcpy(input, new_input);
    free(new_input);
}