#include "main.h"

int main() {
    initialize_command_history();

    while (1) {
        print_prompt();

        char* input = read_input();
        if (input == NULL || is_all_whitespace(input)) continue;

        add_to_command_history(input);
        preprocess_input(input);
        command_sequence_init(input);
    }

    return EXIT_SUCCESS;
}
