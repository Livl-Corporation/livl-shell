#include "main.h"

void handle_input(char *input)
{
    if (input == NULL || is_all_whitespace(input))
        return;

    add_to_command_history(input);
    preprocess_input(input);
    command_sequence_init(input);
}

void run_interactive_mode()
{
    while (1)
    {
        print_prompt();

        char *input = malloc(MAX_INPUT_LENGTH * sizeof(char));
        read_input(input);
        handle_input(input);
        free(input);
    }
}

void run_batch_mode(char *argv[], int argc)
{
    char *input = argv[2];
    for (int i = 3; i < argc; i++)
    {
        input = strcat(input, " ");
        input = strcat(input, argv[i]);
    }
    handle_input(input);
}

int main(int argc, char *argv[])
{
    init_command_history();

    if (argc > 2 && (strcmp(argv[1], "-c") && strcmp(argv[1], "--command")) == 0)
    {
        run_batch_mode(argv, argc);
    }
    else if (argc > 1)
    {
        print_info("Usage: %s [-c \"command\"]", argv[0]);
        return EXIT_FAILURE;
    }
    else
    {
        run_interactive_mode();
    }

    return EXIT_SUCCESS;
}
