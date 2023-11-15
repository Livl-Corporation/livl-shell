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

void print_info(const char *text, ...)
{
    printf(BLUE);
    va_list args;
    va_start(args, text);
    vprintf(text, args);
    va_end(args);
    printf(RESET "\n");
}