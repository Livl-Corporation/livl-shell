#include "scheduler.h"

int execute_external_command(const Command *command) {
    pid_t pid = fork();
    int execution_status;

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == CHILD_PROCESS) {
         // Check for input redirection
        if (command->redirection.input_file != NULL) {
            int in;
            if (command->redirection.append_input) {  // If the "<<" operator was used
                // Create a temporary file
                in = open("/tmp/here_document", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
                
                // Read lines from the terminal until the delimiter is encountered
                char line[256];
                while (1) {
                    printf("> ");  // Print the prompt symbol
                    fflush(stdout);  // Ensure the prompt is displayed immediately
                    if (fgets(line, sizeof(line), stdin) == NULL) {
                        break;  // End of input
                    }

                    // Remove newline character from the end of the line
                    line[strcspn(line, "\n")] = '\0';

                    if (strcmp(line, command->redirection.input_file) == 0) {
                        break;  // End of here document
                    }

                    write(in, line, strlen(line));
                    write(in, "\n", 1);  // Add newline character back when writing to the file
                }


                // Close the file and reopen it for reading
                close(in);
                in = open("/tmp/here_document", O_RDONLY);
            } else {  // If the "<" operator was used
                in = open(command->redirection.input_file, O_RDONLY);
            }
            dup2(in, STDIN_FILENO);
            close(in);
        }

        // Check for output redirection
        if (command->redirection.output_file != NULL) {
            int out;
            if (command->redirection.append_output) {  // If the ">>" operator was used
                out = open(command->redirection.output_file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
            } else {  // If the ">" operator was used
                out = open(command->redirection.output_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
            }
            dup2(out, STDOUT_FILENO);
            close(out);
        }

        if(execvp(command->command, command->complete_command) < 0) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } 

    // Processus père
    waitpid(pid, &execution_status, 0);
    return execution_status;
}


int executeCommand(const Command *command) {
    if (isRedirectionCommand(command)) {
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
