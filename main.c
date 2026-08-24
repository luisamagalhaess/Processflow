#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
            if (tarefa.qtdArgumentos >= 50) {
                printf("Quantidade maxima de argumentos excedida!\n");
                return;
            }
            strcpy(tarefa.argumentos[tarefa.qtdArgumentos], parte);
            tarefa.qtdArgumentos++;
            parte = strtok(NULL, " ");
        }

        if (qtdTarefas >= 100) {
            printf("Limite maximo de tarefas atingido!\n");
            return;
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

        if (strcmp(parte, "sequential") == 0) {
            printf("Modo sequencial!\n");
            parte = strtok(NULL, " ");

            if (parte == NULL) {
                printf("Nenhuma tarefa informada!\n");
                return;
            }

            while (parte != NULL) {
                int posicao = buscarTarefa(parte);

                if (posicao == -1) {
                    printf("Tarefa %s não encontrada!\n", parte);

                } else {
                    printf("Executando tarefa: %s\n", tarefas[posicao].nome);
                    fflush(stdout);

                    pid_t pid = fork();

                    if (pid < 0) {
                        printf("Erro ao criar processo!\n");
                        parte = strtok(NULL, " ");
                        continue;
                    }

                    if (pid == 0) {
                        char *args[52];
                        args[0] = tarefas[posicao].programa;

                        for (int i = 0; i < tarefas[posicao].qtdArgumentos; i++) {
                            args[i + 1] = tarefas[posicao].argumentos[i];
                        }

                        args[tarefas[posicao].qtdArgumentos + 1] = NULL;
                        execvp(tarefas[posicao].programa, args);

                        fprintf(stderr, "Erro ao executar programa!\n");
                        _exit(1);

                    } else {
                        int status;
                        waitpid(pid, &status, 0);

                        if (WIFEXITED(status)) {
                            int codigo = WEXITSTATUS(status);
                            if (codigo != 0) {
                                printf("Processo terminou com código %d\n", codigo);
                            }
                        }
                    }
                }
                parte = strtok(NULL, " ");
            }
        } else if(strcmp(parte, "parallel") == 0) {
            printf("Modo paralelo!\n");
            pid_t pids[100];
            int qtdPids = 0;

            parte = strtok(NULL, " ");

            if (parte == NULL) {
                printf("Nenhuma tarefa informada!\n");
                return;
            }

            while (parte != NULL) {
                int posicao = buscarTarefa(parte);
                if (posicao == -1) {
                    printf("Tarefa %s não encontrada!\n", parte);
                } else {
                    printf("Executando tarefa: %s\n", tarefas[posicao].nome);
                    fflush(stdout);
                    pid_t pid = fork();

                    if (pid < 0) {
                        printf("Erro ao criar processo!\n");
                    } else if (pid == 0) {
                        char *args[52];
                        args[0] = tarefas[posicao].programa;

                        for (int i = 0; i < tarefas[posicao].qtdArgumentos; i++) {
                            args[i + 1] = tarefas[posicao].argumentos[i];
                        }
                        args[tarefas[posicao].qtdArgumentos + 1] = NULL;
                        execvp(tarefas[posicao].programa, args);

                        fprintf(stderr, "Erro ao executar programa!\n");
                        _exit(1);
                    } else {
                        pids[qtdPids] = pid;
                        qtdPids++;
                    }
                }
                parte = strtok(NULL, " ");
            }
            for (int i = 0; i < qtdPids; i++) {
                int status;
                waitpid(pids[i], &status, 0);
                if (WIFEXITED(status)) {
                    int codigo = WEXITSTATUS(status);
                    if (codigo != 0) {
                        printf("Processo terminou com código %d\n", codigo);
                    }
                }
            }            
        } else {

            int posicao = buscarTarefa(parte);

            if (posicao == -1) {
                printf("Tarefa não encontrada!\n");
                return;
            }

            printf("Tarefa encontrada: %s\n", tarefas[posicao].nome);
            pid_t pid = fork();

            if (pid < 0) {
                printf("Erro ao criar processo!\n");
                return;
            }

            if (pid == 0) {
                char *args[52];

                args[0] = tarefas[posicao].programa;

                for (int i = 0; i < tarefas[posicao].qtdArgumentos; i++) {
                    args[i + 1] = tarefas[posicao].argumentos[i];
                }

                args[tarefas[posicao].qtdArgumentos + 1] = NULL;

                execvp(tarefas[posicao].programa, args);

                fprintf(stderr, "Erro ao executar programa!\n");
                _exit(1);
            } else {
                printf("Processo pai!\n");
                int status;
                waitpid(pid, &status, 0);

                if (WIFEXITED(status)) {
                    int codigo = WEXITSTATUS(status);
                    if (codigo != 0) {
                        printf("Processo terminou com código %d\n", codigo);
                    }
                }
            }
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