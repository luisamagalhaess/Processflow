# ProcessFlow

ProcessFlow é um orquestrador de processos desenvolvido em C para a disciplina de Sistemas Operacionais.

O programa permite cadastrar e executar tarefas utilizando processos do sistema operacional, fazendo uso de funções como `fork()`, `execvp()`, `waitpid()` e `dup2()`.

## Compilação

Para compilar o programa, execute:

```bash
make processflow
```

Também é possível compilar diretamente utilizando:

```bash
gcc main.c -o processflow
```

## Execução

### Modo interativo

Para iniciar o ProcessFlow no modo interativo:

```bash
./processflow
```

O programa exibirá o prompt:

```text
processflow>
```

### Modo workflow

Também é possível executar comandos armazenados em um arquivo `.pf`:

```bash
./processflow arquivo.pf
```

Exemplo:

```bash
./processflow teste.pf
```

## Comandos

### task

Cadastra uma nova tarefa.

Sintaxe:

```text
task <nome> <programa> [argumentos]
```

Exemplo:

```text
task listar /bin/ls -l
```

---

### run

Executa uma tarefa cadastrada.

Sintaxe:

```text
run <nome>
```

Exemplo:

```text
run listar
```

---

### run sequential

Executa várias tarefas sequencialmente. Cada tarefa termina antes da execução da próxima.

Sintaxe:

```text
run sequential <tarefa1> <tarefa2> ...
```

Exemplo:

```text
run sequential esperar listar
```

---

### run parallel

Executa várias tarefas de forma paralela.

Sintaxe:

```text
run parallel <tarefa1> <tarefa2> ...
```

Exemplo:

```text
run parallel espera3 espera2
```

---

### input

Redireciona a entrada padrão de uma tarefa para um arquivo.

Sintaxe:

```text
input <tarefa> <arquivo>
```

Exemplo:

```text
input mostrar entrada.txt
```

---

### output

Redireciona a saída padrão de uma tarefa para um arquivo, substituindo o conteúdo anterior.

Sintaxe:

```text
output <tarefa> <arquivo>
```

Exemplo:

```text
output listar resultado.txt
```

---

### append

Redireciona a saída padrão de uma tarefa para o final de um arquivo, preservando o conteúdo existente.

Sintaxe:

```text
append <tarefa> <arquivo>
```

Exemplo:

```text
append listar historico.txt
```

---

### exit

Encerra o ProcessFlow.

```text
exit
```

## Redirecionamento

O ProcessFlow utiliza descritores de arquivos e `dup2()` para realizar o redirecionamento de entrada e saída das tarefas.

- `input`: redireciona `stdin`;
- `output`: redireciona `stdout` e sobrescreve o arquivo;
- `append`: redireciona `stdout` e adiciona o novo conteúdo ao final do arquivo.

## Processos

A execução das tarefas utiliza chamadas de sistema do Linux, incluindo:

- `fork()` para criação de processos filhos;
- `execvp()` para execução dos programas;
- `waitpid()` para aguardar a finalização dos processos;
- `dup2()` para redirecionamento de entrada e saída.

## Makefile

O projeto possui os seguintes comandos:

```bash
make processflow
```

Compila o programa.

```bash
make run
```

Executa o ProcessFlow.

```bash
make clean
```

Remove o executável gerado.

## Requisitos

- Sistema Linux, Unix ou ambiente compatível;
- GCC;
- Make.

## Estrutura atual

```text
Processflow/
├── main.c
├── makefile
├── README.md
└── teste.pf
```

## Autora

Luísa Magalhães