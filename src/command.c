#include "command.h"

Command evaluateCommand(const char *input) {
    Command cmd;
    cmd.command = NULL;
    cmd.arguments = NULL;
    cmd.complete_command = NULL;
    cmd.num_arguments = 0;

    // Copie de la commande d'origine pour la manipulation
    char *input_copy = strdup(input);

    // Découpage en tokens
    char *token = strtok(input_copy, " \t\n"); // Espaces, tabulations et sauts de ligne comme délimiteurs

    // 1. La première partie est le nom de la commande
    if (token != NULL) {
        cmd.command = strdup(token);
    } else {
        // Gestion d'une entrée vide ou malformée
        fprintf(stderr, "Invalid command\n");
        free(input_copy);
        return cmd;
    }

    // 2. Après avoir récupéré le nom de la commande, on récupère tous les arguments
    while ((token = strtok(NULL, "\r\n\t")) != NULL) {
        char **temp = realloc(cmd.arguments, (cmd.num_arguments + 1) * sizeof(char *));
        if (temp == NULL) {
            // Gérer l'échec de l'allocation de mémoire
            fprintf(stderr, "Memory allocation failed\n");
            freeCommand(&cmd);
            exit(EXIT_FAILURE);
        }
        cmd.arguments = temp;
        cmd.arguments[cmd.num_arguments] = strdup(token);
        cmd.num_arguments++;
    }

    // 2.2 Ajout du NULL à la fin du tableau d'arguments pour indiquer la fin du tableau à execvp
    char **temp = realloc(cmd.arguments, (cmd.num_arguments + 1) * sizeof(char *));
    if (temp == NULL) {
        // Gérer l'échec de l'allocation de mémoire
        fprintf(stderr, "Memory allocation failed\n");
        freeCommand(&cmd);
        exit(EXIT_FAILURE);
    }
    cmd.arguments = temp;
    cmd.arguments[cmd.num_arguments] = NULL;

    // 3. On récupère la commande complète
    cmd.complete_command = getCompleteCommand(&cmd);

    free(input_copy);

    return cmd;
}


void printCommand(Command *cmd)
{
    printf(" * Command to execute: %s ", cmd->command);
    for (int i = 0; i < cmd->num_arguments; ++i) {
        printf("%s ", cmd->arguments[i]);
    }
    printf("\n");
}

char** getCompleteCommand(Command *cmd) {
    char **new_arguments = malloc((cmd->num_arguments + 2) * sizeof(char *));
    if (new_arguments == NULL) {
        // Gérer l'échec de l'allocation de mémoire
        fprintf(stderr, "Memory allocation failed\n");
        freeCommand(cmd);
        exit(EXIT_FAILURE);
    }
    new_arguments[0] = cmd->command;
    for (int i = 0; i < cmd->num_arguments; ++i) {
        new_arguments[i + 1] = cmd->arguments[i];
    }
    return new_arguments;
}

void freeCommand(Command *cmd) {
    free(cmd->command);
    for (int i = 0; i < cmd->num_arguments; ++i) {
        free(cmd->arguments[i]);
    }
    free(cmd->arguments);
    free(cmd->complete_command);
}
