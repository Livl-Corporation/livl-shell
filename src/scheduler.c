#include "scheduler.h"

int execute_external_command(const Command *command) {
    pid_t pid = fork();
    int execution_status;

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == CHILD_PROCESS) {
        handle_input_redirection(command);
        handle_output_redirection(command);

        if(execvp(command->command, command->complete_command) < 0) {
            print_perror("%s: command not found. ", command->command);
            exit(EXIT_FAILURE);
        }
    } 

    waitpid(pid, &execution_status, 0);
    return execution_status;
}


int executeCommand(const Command *command) {
    if (is_redirection_command(command)) {
        return execute_external_command(command);
    }

    int execution_status = execute_builtin_command(command);

    if (execution_status == IS_NOT_BUILTIN_COMMAND) {
        execution_status = execute_external_command(command);
    }

    return execution_status;
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
        }  else if(strcmp(sequence->operators[i], ">") == 0) {
            skipNext = 1;
            continue;
        }  else if(strcmp(sequence->operators[i], "<") == 0) {
            skipNext = 1;
            continue;
        }  else if(strcmp(sequence->operators[i], ">>") == 0) {
            skipNext = 1;
            continue;
        }  else if(strcmp(sequence->operators[i], "<<") == 0) {
            skipNext = 1;
            continue;
        }
         else if(strcmp(sequence->operators[i], "|") == 0) {
            continue;
        }  else if(strcmp(sequence->operators[i], "&") == 0) {
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
