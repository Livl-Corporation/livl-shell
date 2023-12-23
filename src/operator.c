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
    for (int i = 0; i < num_operators; i++) {
        if (strcmp(token, operators[i]) == 0) {
            return 1; // The token is an operator
        }
    }

    return 0; // The token is not an operator
}

OperatorType get_operator_type(const char *operator_str) {
    for (int i = 0; i < num_operators; i++) {
        if (strcmp(operator_str, operators[i]) == 0) {
            return (OperatorType)i;
        }
    }
    return UNKNOWN;
}

const char *get_operator_string(OperatorType op) {
    if (op >= 0 && op < num_operators) {
        return operators[op];
    }
    return "UNKNOWN";
}
