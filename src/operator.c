#include "operator.h"

const char *operators[] = {
    ";",
    "&&",
    "||",
    "|",
    "&",
    "<",
    ">",
    ">>",
    "<<"
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
