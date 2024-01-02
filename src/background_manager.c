#include "background_manager.h"

static BackgroundProcess background_processes[MAX_BACKGROUND_PROCESSES];
static size_t num_background_processes = 0;

void check_completed_background_processes()
{
    size_t i = 0;
    while (i < num_background_processes)
    {
        pid_t pid = background_processes[i].pid;
        int status;
        int result = waitpid(pid, &status, WNOHANG);
        if (result == -1)
        {
            perror("waitpid");
        }
        else if (result > 0)
        { // The process with PID 'pid' has completed
            // Display the correct symbol based on the exit status
            char symbol = i == num_background_processes - 1 ? '+' : i == num_background_processes - 2 ? '-'
                                                                                                      : ' ';
            printf("[%d]%c  Done                    %s\n", background_processes[i].job_number, symbol, background_processes[i].command);

            // Free the memory for the completed process command
            free(background_processes[i].command);

            // Remove the completed process from the list
            for (size_t j = i; j < num_background_processes - 1; ++j)
            {
                background_processes[j] = background_processes[j + 1];
            }
            num_background_processes--;
        }
        else
        {
            // Move to the next background process if the current one hasn't completed
            i++;
        }
    }
}

void add_background_process(pid_t pid, const Command *command)
{
    background_processes[num_background_processes].pid = pid;
    background_processes[num_background_processes].job_number = num_background_processes + 1;
    background_processes[num_background_processes].command = strdup(command->input_string);

    if (background_processes[num_background_processes].command == NULL) {
        perror("strdup");
        exit(EXIT_FAILURE);
    }    
    
    printf("[%d] %d %s\n", background_processes[num_background_processes].job_number, pid, background_processes[num_background_processes].command);
    num_background_processes++;
}