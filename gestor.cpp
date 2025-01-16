#include <stdio.h>
#include <string.h>

#define MAX_TAREFAS 10
#define TAM_TAREFA 50

int main() {
    char tarefas[MAX_TAREFAS][TAM_TAREFA];
    int totalTarefas = 0;
    int escolha;

    do {
        printf("\nGestor de Tarefas\n");
        printf("1. Adicionar Tarefa\n");
        printf("2. Listar Tarefas\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);
        getchar(); // Limpar o buffer do teclado

        switch (escolha) {
            case 1:
                if (totalTarefas < MAX_TAREFAS) {
                    printf("Digite a tarefa: ");
                    fgets(tarefas[totalTarefas], TAM_TAREFA, stdin);
                    tarefas[totalTarefas][strcspn(tarefas[totalTarefas], "\n")] = '\0'; // Remover nova linha
                    totalTarefas++;
                    printf("Tarefa adicionada com sucesso!\n");
                } else {
                    printf("Limite de tarefas atingido!\n");
                }
                break;
            case 2:
                printf("\nLista de Tarefas:\n");
                for (int i = 0; i < totalTarefas; i++) {
                    printf("%d. %s\n", i + 1, tarefas[i]);
                }
                break;
            case 3:
                printf("A sair...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (escolha != 3);

    return 0;
}
