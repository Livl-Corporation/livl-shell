#include "scheduler.h"

int executeCommand(const Command *cmd) {
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

    for (size_t i = 0; i < sequence->num_commands; ++i) {
        status = executeCommand(&(sequence->commands[i]));

        // If an error occurs or a command fails, break the loop
        if (status != 0) {
            break;
        }

        // If there are more commands, execute the next one based on the operator
        if (i < sequence->num_commands - 1) {
            if (strcmp(sequence->operators[i], "&&") == 0) {
                // Execute next command only if the previous one succeeded
                if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                    continue;
                } else {
                    break;
                }
            } else if(strcmp(sequence->operators[i], "||") == 0) {
                // Execute next command only if the previous one failed
                if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                    continue;
                } else {
                    break;
                }
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
    }

    return status;
}
