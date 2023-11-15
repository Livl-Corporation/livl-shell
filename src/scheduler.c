#include "scheduler.h"

int executeCommand(const Command *cmd) {
    pid_t pid = fork();
    int status;

    if (pid < 0) {
        perror("fork"); // En cas d'erreur
        exit(EXIT_FAILURE);
        return EXIT_FAILURE;
    }

    if (pid == CHILD_PROCESS) {
        if(execvp(cmd->command, cmd->complete_command) < 0) {
            perror("execvp");
            exit(EXIT_FAILURE);
            return EXIT_FAILURE;
        }
    } 

    // Processus père
    waitpid(pid, &status, 0);
    return status;
}

int executeCommands(const Command *cmd1, const Command *cmd2, const char *control_operator) {

    int status = executeCommand(cmd1);

    // Vérification du statut de la première commande
    if ((WIFEXITED(status) && WEXITSTATUS(status) == 0 && strcmp(control_operator, "&&") == 0) ||
        (WIFEXITED(status) && WEXITSTATUS(status) != 0 && strcmp(control_operator, "||") == 0)) {
        // La première commande s'est terminée avec succès (pour &&) ou a échoué (pour ||),
        // exécuter la deuxième commande
        status = executeCommand(cmd2);
    }

    return status;
}