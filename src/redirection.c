#include "redirection.h"

void handle_input_redirection(const Command *command) {
    if (command->redirection.input_file == NULL) return;

    int in;
    if (command->redirection.append_input) {  // If the "<<" operator was used
        // Create a temporary file
        in = open("/tmp/redirection_input", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
        
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
        in = open("/tmp/redirection_input", O_RDONLY);
    } else {  // If the "<" operator was used
        in = open(command->redirection.input_file, O_RDONLY);
    }
    dup2(in, STDIN_FILENO);
    close(in);
}

void handle_output_redirection(const Command *command) {
    if (command->redirection.output_file == NULL) return; 

    int out;
    if (command->redirection.append_output) {  // If the ">>" operator was used
        out = open(command->redirection.output_file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
    } else {  // If the ">" operator was used
        out = open(command->redirection.output_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
    }
    dup2(out, STDOUT_FILENO);
    close(out);
}

void evaluate_redirection(CommandSequence *sequence) 
{
    for (int i = 0; i < sequence->num_commands-1; ++i) {
        Command *cmd = &sequence->commands[i];

        // Get the operator between the current command and the next one
        char *operator = sequence->operators[i];

        if (strcmp(operator, "<") == 0) {
            // Input redirection
            if (i < sequence->num_commands - 1) {
                Command *next_cmd = &sequence->commands[i + 1];
                cmd->redirection.input_file = strdup(next_cmd->command);
            } else {
                fprintf(stderr, "Missing command after input redirection\n");
                break;
            }
        } else if (strcmp(operator, "<<") == 0) {
            // Input redirection (append)
            if (i < sequence->num_commands - 1) {
                Command *next_cmd = &sequence->commands[i + 1];
                cmd->redirection.input_file = strdup(next_cmd->command);
                cmd->redirection.append_input = 1;
            } else {
                fprintf(stderr, "Missing command after input redirection\n");
                break;
            }
        }
        else if (strcmp(operator, ">") == 0) {
            // Output redirection
            if (i < sequence->num_commands - 1) {
                Command *next_cmd = &sequence->commands[i + 1];
                cmd->redirection.output_file = strdup(next_cmd->command);
            } else {
                fprintf(stderr, "Missing command after output redirection\n");
                break;
            }
        } else if (strcmp(operator, ">>") == 0) {
            // Output redirection (append)
            if (i < sequence->num_commands - 1) {
                Command *next_cmd = &sequence->commands[i + 1];
                cmd->redirection.output_file = strdup(next_cmd->command);
                cmd->redirection.append_output = 1;
            } else {
                fprintf(stderr, "Missing command after output redirection\n");
                break;
            }
        }
    }
}

int is_redirection_command(const Command *command) {
    return command->redirection.input_file != NULL || command->redirection.output_file != NULL;
}
