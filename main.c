#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

    char comando[100];

    if (argc > 2) {
        printf("Número incorreto de argumentos!\n");
        return 1;
    }

    if (argc == 2) {

        FILE *arquivo = fopen(argv[1], "r");

        if (arquivo == NULL) {
            printf("Não foi possível abrir o arquivo!\n");
            return 1;
        }

        while (fgets(comando, 100, arquivo) != NULL) {

            comando[strcspn(comando, "\n")] = '\0';

            printf("%s\n", comando);

            if (strcmp(comando, "exit") == 0) {
                break;
            }
        }

        fclose(arquivo);

    } else {

        while (1) {

            printf("processflow> ");

            if (fgets(comando, 100, stdin) == NULL) {
                break;
            }

            comando[strcspn(comando, "\n")] = '\0';

            if (strcmp(comando, "exit") == 0) {
                break;
            }
        }
    }

    return 0;
}