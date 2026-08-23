#include <stdio.h>
#include <string.h>

typedef struct task {
    char nome[100];
    char programa[100];
    char argumentos[50][100];
    int qtdArgumentos;
} task;

task tarefas[100];
int qtdTarefas = 0;

int buscarTarefa(char *nome) {
    
    for (int i = 0; i < qtdTarefas; i++) {
        if (strcmp(tarefas[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

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
        tarefa.qtdArgumentos = 0;
        parte = strtok(NULL, " ");

        while(parte != NULL) {
            strcpy(tarefa.argumentos[tarefa.qtdArgumentos], parte);
            tarefa.qtdArgumentos++;
            parte = strtok(NULL, " ");
        }
        tarefas[qtdTarefas] = tarefa;
        qtdTarefas++;
        printf("Tarefa %s cadastrada!\n", tarefa.nome);
        printf("Nome: %s\n", tarefa.nome);
        printf("Programa: %s\n", tarefa.programa);
        for (int j = 0; j < tarefa.qtdArgumentos; j++) {
            printf("argumentos[%d]: %s\n", j, tarefa.argumentos[j]);
        }
    } else if (strcmp(parte, "run") == 0){
        parte = strtok(NULL, " ");

        if (parte == NULL) {
            printf("Nome da tarefa não informado!\n");
            return;
        }

        int posicao = buscarTarefa(parte);

        if (posicao == -1) {
            printf("Tarefa não encontrada!\n");
            return;
        }

        printf("Tarefa encontrada: %s\n", tarefas[posicao].nome);
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