#include "console.h"

void print_title()
{
    printf("\n" YELB"    __    _____    ____       _____ __  __________    __  " RESET);
    printf("\n" YELB"   / /   /  _/ |  / / /      / ___// / / / ____/ /   / /  " RESET);
    printf("\n" YELB"  / /    / / | | / / /       \\__ \\/ /_/ / __/ / /   / /   " RESET);
    printf("\n" YELB" / /____/ /  | |/ / /___    ___/ / __  / /___/ /___/ /___ " RESET);
    printf("\n" YELB"/_____/___/  |___/_____/   /____/_/ /_/_____/_____/_____/ " RESET);
    printf("\n" YELB"                                                          "RESET "\n\n");
}

void print_perror(const char *format, ...) {
    va_list args;
    va_start(args, format);

    vfprintf(stderr, format, args);
    perror("");

    va_end(args);
}

void print_info(const char *text, ...)
{
    printf(BLUE);
    va_list args;
    va_start(args, text);
    vprintf(text, args);
    va_end(args);
    printf(RESET "\n");
}

void print_prompt()
{
    char* username = getenv("USER");
    if(username == NULL)
        username = "username";

    // Use this if you want to print the hostname
    // char hostname[1024];
    // gethostname(hostname, 1024);
    // if(username == NULL)
    //     username = "hostname";

    printf(YELLOW "%s" RESET "@" BLUE "livl-bash" RESET ":$ ", username);
}