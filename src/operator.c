#include "operator.h"

/**
 * Order by operator length (longest first) to avoid matching << when looking for <
*/
const char *operators[] = {
    "&&",
    "||",
    ">>",
    "<<",
    ";",
    "|",
    "&",
    "<",
    ">",
};

const int num_operators = sizeof(operators) / sizeof(char*);

int is_operator(const char *token) {
    int num_operators = sizeof(operators) / sizeof(char*);

    for (int i = 0; i < num_operators; i++) {
        if (strcmp(token, operators[i]) == 0) {
            return 1; // The token is an operator
        }
    }

    return 0; // The token is not an operator
}

int is_redirection_operator(const char *token) {
    return strcmp(token, "<") == 0 || strcmp(token, "<<") == 0 || strcmp(token, ">") == 0 || strcmp(token, ">>") == 0;
}
