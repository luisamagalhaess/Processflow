#include <stdio.h>
#include <string.h>

typedef struct task {
    char nome[100];
    char programa[100];
    char *argumentos[50];
} task;

void receberComando(char *comando) {
    
    char *parte = strtok(comando, " ");

    if (parte == NULL) {
        return;
    }

    if(strcmp(parte, "task") == 0) {
        printf("Comando task!\n");

        parte = strtok(NULL, " ");

        task tarefa;
        if (parte == NULL) {
            printf("Nome da tarefa não informado!\n");
            return;
        }
        strcpy(tarefa.nome, parte);

        parte = strtok(NULL, " ");
        if (parte == NULL) {
            printf("Nome do programa nao informado!\n");
            return;
        }
        strcpy(tarefa.programa, parte);

        parte = strtok(NULL, " ");
        int i = 0;

        tarefa.argumentos[i] = tarefa.programa;
        i++;

        while(parte != NULL) {
            tarefa.argumentos[i] = parte;
            i++;

            parte = strtok(NULL, " ");
        }
        tarefa.argumentos[i] = NULL;

        printf("Nome: %s\n", tarefa.nome);
        printf("Programa: %s\n", tarefa.programa);
        for (int j = 0; tarefa.argumentos[j] != NULL; j++) {
            printf("argumentos[%d]: %s\n", j, tarefa.argumentos[j]);
        }
    }
}

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
            receberComando(comando);
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
            receberComando(comando);
        }
    }

    return 0;
}