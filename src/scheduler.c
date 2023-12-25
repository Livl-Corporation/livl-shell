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

int execute_command_sequence(const CommandSequence *sequence) {
    int status = 0;
    int is_current_command_failed = 0;
    int is_skipping_next_command = 0;
    OperatorType current_operator;
    int is_running_in_background = 0;
    const int last_command = sequence->num_commands - 1;

    for (size_t i = 0; i < sequence->num_commands; ++i) {
        is_running_in_background = 0;
        current_operator = UNKNOWN;

        if (is_skipping_next_command) {
            is_skipping_next_command = 0;
            continue;
        }

        if(sequence->operators[i] != NULL) 
            current_operator = get_operator_type(sequence->operators[i]);

        // Before executing the current command, check if it is a pipe or a background operator
        if(current_operator == PIPE && i < last_command) {
            execute_pipe(&(sequence->commands[i]), &(sequence->commands[i + 1]));
            is_skipping_next_command = 1;
            continue; // No need to execute the current command because it is a pipe
        } else if (current_operator == BACKGROUND) {
            is_running_in_background = 1;
        }

        status = execute_command(&(sequence->commands[i]), is_running_in_background);
        is_current_command_failed = WIFEXITED(status) && WEXITSTATUS(status) == 0;

        // If the current command is the last one, break the loop because there is no next command
        if (i == last_command) break;

        switch (current_operator) {
            case AND:
                is_skipping_next_command = (is_current_command_failed == 0);
                break;
            case OR:
                is_skipping_next_command = (is_current_command_failed != 0);
                break;
            case REDIRECTION_APPEND_OUTPUT:
            case REDIRECTION_APPEND_INPUT:
            case REDIRECTION_OUTPUT:
            case REDIRECTION_INPUT:
                is_skipping_next_command = 1; // Skip the next command because it is a redirection
                break;
            case SEMICOLON:
            case PIPE:
            case BACKGROUND:
                break; // Continue to the next command
            case UNKNOWN:
                fprintf(stderr, "Unsupported operator: %s\n", sequence->operators[i]);
                status = EXIT_FAILURE;
                break;
        }
    }

    check_completed_background_processes();

    return status;
}
