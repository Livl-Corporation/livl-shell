#include "operator.h"

/**
 * Order by operator length (longest first) to avoid matching << when looking for <
 */
OperatorType get_operator_type(const char *operator_str)
{

    if (operator_str == NULL)
    {
        return UNKNOWN;
    }

    if (strcmp(operator_str, "&&") == 0)
    {
        return AND;
    }

    if (strcmp(operator_str, "||") == 0)
    {
        return OR;
    }

    if (strcmp(operator_str, ">>") == 0)
    {
        return REDIRECTION_APPEND_OUTPUT;
    }

    if (strcmp(operator_str, "<<") == 0)
    {
        return REDIRECTION_APPEND_INPUT;
    }

    if (strcmp(operator_str, ";") == 0)
    {
        return SEMICOLON;
    }

    if (strcmp(operator_str, "|") == 0)
    {
        return PIPE;
    }

    if (strcmp(operator_str, "&") == 0)
    {
        return BACKGROUND;
    }

    if (strcmp(operator_str, ">") == 0)
    {
        return REDIRECTION_OUTPUT;
    }

    if (strcmp(operator_str, "<") == 0)
    {
        return REDIRECTION_INPUT;
    }

    return UNKNOWN;
}

const char *get_operator_string(OperatorType operator_type)
{

    switch (operator_type)
    {
    case AND:
        return "&&";
    case OR:
        return "||";
    case REDIRECTION_APPEND_OUTPUT:
        return ">>";
    case REDIRECTION_APPEND_INPUT:
        return "<<";
    case SEMICOLON:
        return ";";
    case PIPE:
        return "|";
    case BACKGROUND:
        return "&";
    case REDIRECTION_OUTPUT:
        return ">";
    case REDIRECTION_INPUT:
        return "<";
    default:
        return "UNKNOWN";
    }
}