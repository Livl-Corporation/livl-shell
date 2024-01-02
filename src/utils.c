#include "utils.h"

char *trim(char *str)
{
    char *end;

    // Trim leading whitespace
    while (isspace((unsigned char)*str))
        str++;

    if (*str == 0) // Only whitespace
        return str;

    // Trim trailing whitespace
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    // Write new null terminator
    *(end + 1) = 0;

    return str;
}

void handle_quotes(char *token)
{
    char quote_type = token[0];
    if (quote_type == '"' || quote_type == '\'')
    {
        char *end_quote = strchr(&token[1], quote_type);

        if (end_quote != NULL)
        {
            *end_quote = '\0';                        // Remove the end quotation mark
            memmove(token, token + 1, strlen(token)); // Remove the start quotation mark
        }
    }
}