#include "main.h"

int ready() {
    print_info("prompt> ls -l && pwd");

    const char *input1 = "ls -l";
    const char *input2 = "pwd";

    Command cmd1 = evaluateCommand(input1);
    Command cmd2 = evaluateCommand(input2);

    // Exécution séquentielle (&&)
    executeCommands(&cmd1, &cmd2, "&&");

    // Libération de la mémoire
    freeCommand(&cmd1);
    freeCommand(&cmd2);


    // char* expression ;
    // scanf("%s", &expression);

    // évaluer les expressions

        // obtenir chaque commande séparée par &&, ||, ;, |, &, >, >>, <
        // identifier la commande, les opérateurs et les arguments
        

    // ordonancement : pour chaque commande

        // Commmande interne ?

        // Sinon execution de la commande comme processus fils

        // on traite le résultat (=> envoyer dans la commande suivante ou afficher)

    return EXIT_SUCCESS;
}

int main(int argc, char** argv)
{
    print_title();

    ready();

    // while(1) {
    // }
    
    return EXIT_SUCCESS;
}

