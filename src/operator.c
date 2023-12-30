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

    size_t len = 2;

    if (strncmp(operator_str, "&&", len) == 0)
    {
        return AND;
    }

    if (strncmp(operator_str, "||", len) == 0)
    {
        return OR;
    }

    if (strncmp(operator_str, ">>", len) == 0)
    {
        return REDIRECTION_APPEND_OUTPUT;
    }

    if (strncmp(operator_str, "<<", len) == 0)
    {
        return REDIRECTION_APPEND_INPUT;
    }

    len = 1;

    if (strncmp(operator_str, ";", len) == 0)
    {
        return SEMICOLON;
    }

    if (strncmp(operator_str, "|", len) == 0)
    {
        return PIPE;
    }

    if (strncmp(operator_str, "&", len) == 0)
    {
        return BACKGROUND;
    }

    if (strncmp(operator_str, ">", len) == 0)
    {
        return REDIRECTION_OUTPUT;
    }

    if (strncmp(operator_str, "<", len) == 0)
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