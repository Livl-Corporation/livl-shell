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

        command_sequence_init(input);
    }

    return EXIT_SUCCESS;
}
