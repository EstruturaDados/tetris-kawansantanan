#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ---------------------------------------------------------
// STRUCT DA PEÇA
// ---------------------------------------------------------
typedef struct {
    char nome;  // Tipo da peça: I, O, T, L
    int id;     // Identificador único
} Peca;

// ---------------------------------------------------------
// TAMANHOS FIXOS DAS ESTRUTURAS
// ---------------------------------------------------------
#define TAM_FILA 5
#define TAM_PILHA 3

// ---------------------------------------------------------
// FILA CIRCULAR
// ---------------------------------------------------------
Peca fila[TAM_FILA];
int inicio = 0, fim = 0, qtdFila = 0;

// ---------------------------------------------------------
// PILHA
// ---------------------------------------------------------
Peca pilha[TAM_PILHA];
int topo = -1;

// ---------------------------------------------------------
// GERA UMA PEÇA ALEATÓRIA
// ---------------------------------------------------------
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = id;
    return p;
}

// ---------------------------------------------------------
// ENFILEIRAR (INSERIR NA FILA CIRCULAR)
// ---------------------------------------------------------
void enfileirar(Peca p) {
    if (qtdFila == TAM_FILA) {
        printf("\n[ERRO] A fila está cheia!\n");
        return;
    }
    fila[fim] = p;
    fim = (fim + 1) % TAM_FILA;
    qtdFila++;
}

// ---------------------------------------------------------
// DESENFILEIRAR (REMOVER DA FRENTE)
// ---------------------------------------------------------
Peca desenfileirar() {
    Peca erro = {'-', -1};

    if (qtdFila == 0) {
        printf("\n[ERRO] A fila está vazia!\n");
        return erro;
    }

    Peca removida = fila[inicio];
    inicio = (inicio + 1) % TAM_FILA;
    qtdFila--;
    return removida;
}

// ---------------------------------------------------------
// EMPILHAR (PUSH)
// ---------------------------------------------------------
void empilhar(Peca p) {
    if (topo == TAM_PILHA - 1) {
        printf("\n[ERRO] Pilha cheia! Não é possível reservar mais.\n");
        return;
    }
    pilha[++topo] = p;
}

// ---------------------------------------------------------
// DESEMPILHAR (POP)
// ---------------------------------------------------------
Peca desempilhar() {
    Peca erro = {'-', -1};

    if (topo == -1) {
        printf("\n[ERRO] Pilha vazia! Nenhuma peça reservada.\n");
        return erro;
    }

    return pilha[topo--];
}

// ---------------------------------------------------------
// TROCA SIMPLES (FILA <-> PILHA)
// ---------------------------------------------------------
void trocarPeçaAtual() {
    if (topo == -1) {
        printf("\n[ERRO] Não há peça na pilha para trocar!\n");
        return;
    }
    if (qtdFila == 0) {
        printf("\n[ERRO] Fila vazia! Nada a trocar.\n");
        return;
    }

    // índice da frente da fila
    int idxFila = inicio;

    // troca direta
    Peca temp = fila[idxFila];
    fila[idxFila] = pilha[topo];
    pilha[topo] = temp;

    printf("\n[TROCA REALIZADA] Peça da fila trocada com topo da pilha.\n");
}

// ---------------------------------------------------------
// TROCA MÚLTIPLA (3 DA FILA ↔ 3 DA PILHA)
// ---------------------------------------------------------
void trocaMultipla() {
    if (qtdFila < 3 || topo < 2) {
        printf("\n[ERRO] Não há peças suficientes para troca múltipla!\n");
        return;
    }

    for (int i = 0; i < 3; i++) {
        int idxFila = (inicio + i) % TAM_FILA;
        Peca temp = fila[idxFila];
        fila[idxFila] = pilha[topo - i];
        pilha[topo - i] = temp;
    }

    printf("\n[TROCA MÚLTIPLA REALIZADA COM SUCESSO]\n");
}

// ---------------------------------------------------------
// EXIBIÇÃO DA ESTRUTURA
// ---------------------------------------------------------
void exibirEstado() {
    printf("\n=====================================\n");
    printf("        ESTADO ATUAL DO JOGO\n");
    printf("=====================================\n");

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

// ---------------------------------------------------------
// PROGRAMA PRINCIPAL
// ---------------------------------------------------------
int main() {
    srand(time(NULL));

    int idGlobal = 0;

    // Inicializa fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++)
        enfileirar(gerarPeca(idGlobal++));

    int op;

    do {
        exibirEstado();

        printf("\n========== MENU ==========\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("4 - Trocar peça atual (fila ↔ pilha)\n");
        printf("5 - Troca múltipla (3 da fila ↔ 3 da pilha)\n");
        printf("0 - Sair\n");
        printf("==========================\n");
        printf("Opção: ");
        scanf("%d", &op);

        switch (op) {

            case 1: {
                Peca jogada = desenfileirar();
                if (jogada.id != -1)
                    printf("\nPeça jogada: [%c %d]\n", jogada.nome, jogada.id);

                enfileirar(gerarPeca(idGlobal++));
                break;
            }

            case 2: {
                if (qtdFila > 0) {
                    Peca retirada = desenfileirar();
                    empilhar(retirada);
                    printf("\nPeça reservada: [%c %d]\n", retirada.nome, retirada.id);
                    enfileirar(gerarPeca(idGlobal++));
                }
                break;
            }

            case 3: {
                Peca usada = desempilhar();
                if (usada.id != -1)
                    printf("\nPeça usada da pilha: [%c %d]\n", usada.nome, usada.id);
                break;
            }

            case 4:
                trocarPeçaAtual();
                break;

            case 5:
                trocaMultipla();
                break;

            case 0:
                printf("\nEncerrando...\n");
                break;

            default:
                printf("\n[ERRO] Opção inválida!\n");
        }

    } while (op != 0);

    return 0;
}