#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// -----------------------------------------
// Struct que representa uma peça do jogo
// -----------------------------------------
typedef struct {
    char nome;   // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;      // Identificador único
} Peca;

// -----------------------------------------
// Constantes para fila e pilha
// -----------------------------------------
#define TAM_FILA 5
#define TAM_PILHA 3

// -----------------------------------------
// Fila circular (peças futuras)
// -----------------------------------------
Peca fila[TAM_FILA];
int inicio = 0, fim = 0, qtdFila = 0;

// -----------------------------------------
// Pilha (peças reservadas)
// -----------------------------------------
Peca pilha[TAM_PILHA];
int topo = -1;

// -----------------------------------------
// Gerador de peças automáticas
// -----------------------------------------
Peca gerarPeca(int id) {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = id;
    return p;
}

// -----------------------------------------
// Inserir peça no final da fila (enqueue)
// -----------------------------------------
void enfileirar(Peca p) {
    if (qtdFila == TAM_FILA) {
        printf("\nFila cheia! Não foi possível adicionar peça.\n");
        return;
    }
    fila[fim] = p;
    fim = (fim + 1) % TAM_FILA;
    qtdFila++;
}

// -----------------------------------------
// Remover peça da frente da fila (dequeue)
// -----------------------------------------
Peca desenfileirar() {
    Peca removida = {'-', -1};

    if (qtdFila == 0) {
        printf("\nFila vazia!\n");
        return removida;
    }

    removida = fila[inicio];
    inicio = (inicio + 1) % TAM_FILA;
    qtdFila--;

    return removida;
}

// -----------------------------------------
// Empilhar peça (push) na pilha de reserva
// -----------------------------------------
void empilhar(Peca p) {
    if (topo == TAM_PILHA - 1) {
        printf("\nPilha cheia! Não é possível reservar mais peças.\n");
        return;
    }
    pilha[++topo] = p;
}

// -----------------------------------------
// Desempilhar peça (pop) da pilha
// -----------------------------------------
Peca desempilhar() {
    Peca removida = {'-', -1};

    if (topo == -1) {
        printf("\nPilha vazia! Nenhuma peça reservada.\n");
        return removida;
    }

    removida = pilha[topo--];
    return removida;
}

// -----------------------------------------
// Exibir estado atual da fila e da pilha
// -----------------------------------------
void exibirEstado() {
    printf("\n==============================\n");
    printf("   ESTADO ATUAL DO JOGO\n");
    printf("==============================\n");

    printf("\nFila de peças: ");
    if (qtdFila == 0)
        printf("(vazia)");
    else {
        int i = inicio;
        for (int c = 0; c < qtdFila; c++) {
            printf("[%c %d] ", fila[i].nome, fila[i].id);
            i = (i + 1) % TAM_FILA;
        }
    }

    printf("\nPilha de reserva (Topo -> Base): ");
    if (topo == -1)
        printf("(vazia)");
    else {
        for (int i = topo; i >= 0; i--) {
            printf("[%c %d] ", pilha[i].nome, pilha[i].id);
        }
    }

    printf("\n");
}

// -----------------------------------------
// Programa principal
// -----------------------------------------
int main() {
    srand(time(NULL));

    int idGlobal = 0;

    // Inicializa a fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enfileirar(gerarPeca(idGlobal++));
    }

    int opcao;

    do {
        exibirEstado();

        printf("\n=== MENU ===\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1: {
                // Jogar peça (remove da fila e gera nova peça)
                Peca jogada = desenfileirar();
                if (jogada.id != -1)
                    printf("\nPeça jogada: [%c %d]\n", jogada.nome, jogada.id);

                enfileirar(gerarPeca(idGlobal++));
                break;
            }

            case 2: {
                // Reservar peça (da fila para pilha)
                if (qtdFila > 0) {
                    Peca removida = desenfileirar();
                    empilhar(removida);
                    printf("\nPeça reservada: [%c %d]\n", removida.nome, removida.id);
                    enfileirar(gerarPeca(idGlobal++));
                }
                break;
            }

            case 3: {
                // Usar peça da reserva
                Peca usada = desempilhar();
                if (usada.id != -1)
                    printf("\nPeça usada da reserva: [%c %d]\n", usada.nome, usada.id);

                break;
            }

            case 0:
                printf("\nEncerrando...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}