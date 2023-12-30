#include "input_parser.h"

char *read_input(char *input)
{
    if (input == NULL)
    {
        perror("input is not allocated");
        return NULL;
    }

    struct termios old_termios, new_termios;
    tcgetattr(STDIN_FILENO, &old_termios);
    new_termios = old_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    int index = 0;
    int c;
    while ((c = getchar()) != '\n')
    {
        if (c == 27) // Escape character
        {
            getchar(); // Skip the [
            switch (getchar())
            {
            case 'A': // Arrow up
                handle_arrow_up(input, &index);
                break;
            case 'B': // Arrow down
                handle_arrow_down(input, &index);
                break;
            case 'D': // Arrow left
                handle_arrow_left(input, &index);
                break;
            case 'C': // Arrow right
                handle_arrow_right(input, &index);
                break;
            default:
                break;
            }
        }
        else if (c == 127) // Backspace
        {
            handle_backspace(input, &index);
        }
        else if (c == 8) // Control (or command on macos) + backspace
        {
            handle_control_backspace(input, &index);
        }
        else if (isalnum(c) || isspace(c) || ispunct(c)) // Check if the character is alphanumeric, whitespace, or punctuation
        {
            printf("%c", c);
            input[index++] = c;
        }
    }
    input[strlen(input)] = '\0';

    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
    printf("\n");
    reset_current_index();

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
        OperatorType operator_type = get_operator_type(&token);

        if (operator_type != UNKNOWN)
        {

            char *operator_string = get_operator_string(operator_type);
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

void handle_arrow_up(char *input, int *index)
{
    char command[MAX_INPUT_LENGTH];
    get_previous_command(command);
    replace_input(input, index, command);
}

void handle_arrow_down(char *input, int *index)
{
    char command[MAX_INPUT_LENGTH];
    get_next_command(command);
    replace_input(input, index, command);
}

void handle_arrow_left(char *input, int *index)
{
    if (*index > 0)
    {
        printf("\b");
        (*index)--;
    }
}

void handle_arrow_right(char *input, int *index)
{
    if (*index < strlen(input))
    {
        printf("%c", input[*index]);
        (*index)++;
    }
}

void handle_backspace(char *input, int *index)
{
    if (*index == 0)
    {
        return;
    }

    // Shift characters to the left
    for (int i = *index - 1; i < strlen(input); i++)
    {
        input[i] = input[i + 1];
    }

    // Update index
    (*index)--;

    // Print the new input
    printf("\33[2K\r");
    print_prompt();
    printf("%s", input);
    printf("\33[%dD", (int)strlen(input) - *index);
}

void handle_control_backspace(char *input, int *index)
{
    replace_input(input, index, "");
}

void replace_input(char *input, int *index, const char *replacement)
{
    printf("\33[2K\r");
    print_prompt();
    printf("%s", replacement);
    strcpy(input, replacement);
    *index = strlen(replacement);
}