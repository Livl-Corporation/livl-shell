#include "scheduler.h"

int execute_external_command(const Command *command, int run_in_background) {
    pid_t pid = fork();

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
    }  else {
        if (run_in_background) {
            add_background_process(pid, command);
        } else {
            int execution_status;
            waitpid(pid, &execution_status, 0);
            return execution_status;
        }
    }

    return 0;
}


int execute_command(const Command *command, int run_in_background) {
    if (is_redirection_command(command)) {
        return execute_external_command(command, run_in_background);
    }

    int execution_status = execute_builtin_command(command);

    if (execution_status == IS_NOT_BUILTIN_COMMAND) {
        execution_status = execute_external_command(command, run_in_background);
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

        // If there are more commands, execute the next one based on the operator
        if (i < sequence->num_commands - 1) {
            if (strcmp(sequence->operators[i], "|") == 0) {
                // Execute a pipe between the current command and the next command
                execute_pipe(&(sequence->commands[i]), &(sequence->commands[i + 1]));
                skipNext = 1;
                continue;
            }
        }

        // check if the command is a background command
        int run_in_background = 0;
        if (i < sequence->num_commands - 1) {
            if (strcmp(sequence->operators[i], "&") == 0) {
                run_in_background = 1;
            }
        }

        status = execute_command(&(sequence->commands[i]), run_in_background);

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
        } 
        else if(strcmp(sequence->operators[i], "||") == 0) {
            // Execute next command only if the previous one failed
            if (hasFailed != 0) {
                skipNext = 1;
            }
            continue;
        } 
        else if(strcmp(sequence->operators[i], ";") == 0) {
            continue;
        } 
        else if(is_redirection_operator(sequence->operators[i])) {
            skipNext = 1;
            continue;
        }    
        else if(strcmp(sequence->operators[i], "&") == 0) {
            continue;
        }      
        else {
            fprintf(stderr, "Unsupported operator: %s\n", sequence->operators[i]);
            status = EXIT_FAILURE;
            break;
        }
    }

    check_completed_background_processes();

    return status;
}
