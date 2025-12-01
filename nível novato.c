#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5   // Tamanho fixo da fila

// ----------------------------------------
// STRUCT DA PEÇA DO TETRIS
// ----------------------------------------
typedef struct {
    char nome;   // Tipo da peça: I, O, T, L
    int id;      // Identificador único (incremental)
} Peca;

// ----------------------------------------
// VARIÁVEIS GLOBAIS DA FILA CIRCULAR
// ----------------------------------------
Peca fila[MAX];
int inicio = 0;
int fim = 0;
int quantidade = 0;
int idAtual = 0;   // Usado para gerar IDs únicos

// ----------------------------------------
// FUNÇÃO QUE GERA UMA NOVA PEÇA AUTOMATICAMENTE
// ----------------------------------------
Peca gerarPeca() {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4];  // Escolhe um tipo aleatório
    nova.id = idAtual++;
    return nova;
}

// ----------------------------------------
// INSERIR NA FILA (ENQUEUE)
// ----------------------------------------
void enqueue() {
    if (quantidade == MAX) {
        printf("\nA fila está cheia! Não é possível inserir.\n");
        return;
    }

    fila[fim] = gerarPeca();
    fim = (fim + 1) % MAX;
    quantidade++;

    printf("\nPeça inserida com sucesso!\n");
}

// ----------------------------------------
// REMOVER DA FILA (DEQUEUE)
// ----------------------------------------
void dequeue() {
    if (quantidade == 0) {
        printf("\nFila vazia! Não há peça para jogar.\n");
        return;
    }

    Peca removida = fila[inicio];
    inicio = (inicio + 1) % MAX;
    quantidade--;

    printf("\nPeça jogada:\n");
    printf("Tipo: %c | ID: %d\n", removida.nome, removida.id);
}

// ----------------------------------------
// MOSTRAR TODA A FILA
// ----------------------------------------
void mostrarFila() {
    printf("\n===== FILA DE PEÇAS =====\n");

    if (quantidade == 0) {
        printf("A fila está vazia.\n");
        return;
    }

    int idx = inicio;

    for (int i = 0; i < quantidade; i++) {
        printf("[%c %d] ", fila[idx].nome, fila[idx].id);
        idx = (idx + 1) % MAX;
    }

    printf("\n==========================\n");
}

// ----------------------------------------
// FUNÇÃO PRINCIPAL COM MENU
// ----------------------------------------
int main() {
    srand(time(NULL));

    // Inicializa com 5 peças automaticamente
    for (int i = 0; i < MAX; i++) {
        enqueue();
    }

    int opcao;

    do {
        mostrarFila();

        printf("\n===== MENU =====\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue();
                break;
            case 2:
                enqueue();
                break;
            case 0:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}