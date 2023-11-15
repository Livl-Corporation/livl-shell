#include "command.h"

Command evaluateCommand(const char *input) {
    Command cmd;
    cmd.command = NULL;
    cmd.arguments = NULL;
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
        perror("Invalid command");
        free(input_copy);
        return cmd;
    }

    // 2. Après avoir récupéré le nom de la commande, on récupère tous les arguments
    while ((token = strtok(NULL, " \t\n")) != NULL) {
        cmd.arguments = realloc(cmd.arguments, (cmd.num_arguments + 1) * sizeof(char *));
        cmd.arguments[cmd.num_arguments] = strdup(token);
        cmd.num_arguments++;
    }

    free(input_copy);
    return cmd;
}

void printCommand(Command *cmd)
{
    printf("Command: %s\n", cmd->command);
    printf("Arguments: ");
    for (int i = 0; i < cmd->num_arguments; ++i) {
        printf("%s ", cmd->arguments[i]);
    }
    printf("\n");
}

void freeCommand(Command *cmd) {
    free(cmd->command);
    for (int i = 0; i < cmd->num_arguments; ++i) {
        free(cmd->arguments[i]);
    }
    free(cmd->arguments);
}