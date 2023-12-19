#include "scheduler.h"

void cd(char* path) {
    if (chdir(path) != 0) {
        perror("cd");
    }
}

// Implementation of pwd command
void pwd() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("getcwd");
    }
}

void exit_shell() {
    exit(0);
}

void echo(char* message) {
    printf("%s\n", message);
}

int executeCommand(const Command *cmd) {
     if (strcmp(cmd->command, "cd") == 0) {
        // Commande cd
        if (cmd->num_arguments == 1) {
            cd(cmd->arguments[0]);
            return 0;  // La commande a réussi (statut 0)
        } else {
            fprintf(stderr, "Usage: cd <directory>\n");
            return EXIT_FAILURE;  // La commande a échoué
        }
    } else if (strcmp(cmd->command, "pwd") == 0) {
        // Commande pwd
        if (cmd->num_arguments == 0) {
            pwd();
            return 0;  // La commande a réussi (statut 0)
        } else {
            fprintf(stderr, "Usage: pwd\n");
            return EXIT_FAILURE;  // La commande a échoué
        }
    } else if (strcmp(cmd->command, "exit") == 0) {
        // Commande exit
        if (cmd->num_arguments == 0) {
            exit_shell();
            return 0;  // La commande a réussi (statut 0)
        } else {
            fprintf(stderr, "Usage: exit\n");
            return EXIT_FAILURE;  // La commande a échoué
        }
    } else if (strcmp(cmd->command, "echo") == 0) {
        // Commande echo
        if (cmd->num_arguments == 1) {
            echo(cmd->arguments[0]);
            return 0;  // La commande a réussi (statut 0)
        } else {
            fprintf(stderr, "Usage: echo <message>\n");
            return EXIT_FAILURE;  // La commande a échoué
        }
    }

    // Si la commande n'est pas interne, exécutez-la comme une commande externe
    pid_t pid = fork();
    int status;

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == CHILD_PROCESS) {
        if(execvp(cmd->command, cmd->complete_command) < 0) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } 

    // Processus père
    waitpid(pid, &status, 0);
    return status;
}

int executeCommandSequence(const CommandSequence *sequence) {
    int status = 0;

    int hasFailed = 0;
    int skipNext = 0;

    for (size_t i = 0; i < sequence->num_commands; ++i) {
        
        if (skipNext) {
            skipNext = 0;
            continue;
        };

        status = executeCommand(&(sequence->commands[i]));

        hasFailed = WIFEXITED(status) && WEXITSTATUS(status) == 0;

        // If there are more commands, execute the next one based on the operator
        if (i >= sequence->num_commands - 1) {
            break;
        }

        if (strcmp(sequence->operators[i], "&&") == 0) {
            // Execute next command only if the previous one succeeded
            if (hasFailed == 0) {
                skipNext = 1;
            }
            continue;
        } else if(strcmp(sequence->operators[i], "||") == 0) {
            // Execute next command only if the previous one failed
            if (hasFailed != 0) {
                skipNext = 1;
            }
            continue;
        } 
        else if(strcmp(sequence->operators[i], ";") == 0) {
            continue;
        }            
        else {
            fprintf(stderr, "Unsupported operator: %s\n", sequence->operators[i]);
            status = EXIT_FAILURE;
            break;
        }
    }

    return status;
}
