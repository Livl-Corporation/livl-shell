#include "builtin_commands.h"

void cd(char* path) {
    if (chdir(path) != 0) {
        perror("cd");
    }
}

void pwd() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("getcwd");
    }
}

void exit_shell() {
    exit(EXIT_SUCCESS);
}

void echo(const Command *command) {
    for (int i = 0; i < command->num_arguments; i++) {
        printf("%s ", command->arguments[i]);
    }
    printf("\n");
}

int execute_builtin_command(const Command *command) {
    if (strcmp(command->command, "cd") == 0) {
        if (command->num_arguments == 1) {
            cd(command->arguments[0]);
            return IS_BUILTIN_COMMAND;
        } else {
            fprintf(stderr, "Usage: cd <directory>\n");
            return EXIT_FAILURE;
        }
    } else if (strcmp(command->command, "pwd") == 0) {
        if (command->num_arguments == 0) {
            pwd();
            return IS_BUILTIN_COMMAND;
        } else {
            fprintf(stderr, "Usage: pwd\n");
            return EXIT_FAILURE;
        }
    } else if (strcmp(command->command, "exit") == 0) {
        if (command->num_arguments == 0) {
            exit_shell();
            return IS_BUILTIN_COMMAND;
        } else {
            fprintf(stderr, "Usage: exit\n");
            return EXIT_FAILURE; 
        }
    } else if (strcmp(command->command, "echo") == 0) {
        if (command->num_arguments >= 1) {
            echo(command);
            return IS_BUILTIN_COMMAND; 
        } else {
            fprintf(stderr, "Usage: echo <message>\n");
            return EXIT_FAILURE;
        }
    }

    return IS_NOT_BUILTIN_COMMAND;
}