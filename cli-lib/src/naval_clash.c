#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "keyboard.h"
#include "screen.h"
#include "timer.h"

// Cabeçalhos de funções
void menuInicial();
void limpaTela();
void iniciaTabuleiro(char tabuleiro[12][12], char mascara[12][12]);
void exibeMapa();
void exibeTabuleiro(char tabuleiro[12][12], char mascara[12][12], int mostraGabarito);
void posicionaBarcos(char tabuleiro[12][12]);
void verificaTiro(char tabuleiro[12][12], int linha, int coluna, int *pontos, char *mensagem);
void jogo(char nomeJogador[50]);

void limpaTela() {
    screenClear();
}

void iniciaTabuleiro(char tabuleiro[12][12], char mascara[12][12]) {
    for (int linha = 0; linha < 12; linha++) {
        for (int coluna = 0; coluna < 12; coluna++) {
            if (linha == 0 || linha == 11 || coluna == 0 || coluna == 11) {
                tabuleiro[linha][coluna] = 'A';  // Água nas bordas
                mascara[linha][coluna] = 'A';    // Máscara de água nas bordas
            } else {
                tabuleiro[linha][coluna] = ' ';
                mascara[linha][coluna] = '*';
            }
        }
    }
}

void exibeMapa() {
    printf("     ");
    for (int cont = 0; cont < 10; cont++) {
        printf("%d ", cont);
    }
    printf("\n     ");
    for (int cont = 0; cont < 10; cont++) {
        printf("| ");
    }
    printf("\n");
}

void exibeTabuleiro(char tabuleiro[12][12], char mascara[12][12], int mostraGabarito) {
    screenClear();
    screenDrawBorders();  // Desenha borda ao redor do grid
    screenGotoxy(2, 2);   // Posição inicial para centralizar a matriz no grid

    // Exibe a matriz com o grid
    for (int linha = 1; linha < 11; linha++) {
        screenGotoxy(3, linha + 2);  // Centraliza verticalmente
        for (int coluna = 1; coluna < 11; coluna++) {
            if (mascara[linha][coluna] == 'A') {
                printf("\033[1;34m %c \033[0m", mascara[linha][coluna]);  // Azul para água
            } else if (mascara[linha][coluna] == 'P') {
                printf("\033[1;32m %c \033[0m", mascara[linha][coluna]);  // Verde para barcos
            } else {
                printf(" %c ", mascara[linha][coluna]);
            }
        }
        printf("\n");
    }

    if (mostraGabarito) {
        for (int linha = 0; linha < 12; linha++) {
            for (int coluna = 0; coluna < 12; coluna++) {
                printf(" %c", tabuleiro[linha][coluna]);
            }
            printf("\n");
        }
    }
}

void posicionaBarcos(char tabuleiro[12][12]) {
    int barcosPosicionados = 0;
    while (barcosPosicionados < 12) {
        int linha = rand() % 12;
        int coluna = rand() % 12;
        if (tabuleiro[linha][coluna] == 'A') {
            tabuleiro[linha][coluna] = 'B';
            barcosPosicionados++;
        }
    }
}

void verificaTiro(char tabuleiro[12][12], int linha, int coluna, int *pontos, char *mensagem) {
    if (tabuleiro[linha][coluna] == 'B') {
        *pontos += 10;
        strcpy(mensagem, "Você acertou um barco! (10 pts)");
    } else {
        strcpy(mensagem, "Você acertou a água");
    }
}

void jogo(char nomeJogador[50]) {
    char tabuleiro[12][12], mascara[12][12];
    int pontos = 0, tentativas = 0, maximoTentativas = 20;
    char mensagem[100] = "Bem-vindo ao jogo!";
    int linhaJogada, colunaJogada;

    iniciaTabuleiro(tabuleiro, mascara);
    posicionaBarcos(tabuleiro);
    screenInit(1);  // Inicializa a tela com bordas

    while (tentativas < maximoTentativas) {
        limpaTela();
        exibeMapa();
        exibeTabuleiro(tabuleiro, mascara, 0);
        
        printf("\nPontos: %d, Tentativas Restantes: %d", pontos, maximoTentativas - tentativas);
        printf("\n%s\n", mensagem);

        printf("%s, digite uma linha: ", nomeJogador);
        while (!keyhit());  // Aguarda a digitação
        linhaJogada = readch() - '0';  // Converte char para int

        printf("%s, digite uma coluna: ", nomeJogador);
        while (!keyhit());
        colunaJogada = readch() - '0';

        if (linhaJogada >= 0 && linhaJogada < 12 && colunaJogada >= 0 && colunaJogada < 12) {
            verificaTiro(tabuleiro, linhaJogada, colunaJogada, &pontos, mensagem);
            mascara[linhaJogada][colunaJogada] = tabuleiro[linhaJogada][colunaJogada];
            tentativas++;
        } else {
            printf("Posição inválida. Tente novamente.\n");
        }
    }

    screenDestroy();  // Restaura a tela ao estado inicial
    printf("Fim de jogo! Pontuação final: %d\n1-Jogar Novamente\n2-Ir para o Menu\n3-Sair\n", pontos);

    int opcao;
    while (!keyhit());
    opcao = readch() - '0';

    switch(opcao) {
        case 1:
            jogo(nomeJogador);
            break;
        case 2:
            menuInicial();
            break;
        case 3:
            printf("Até mais!\n");
            break;
    }
}

void menuInicial() {
    int opcao = 0;
    char nomeJogador[50];
    int index = 0;

    while (opcao < 1 || opcao > 3) {
        limpaTela();
        printf("Bem-vindo ao Jogo de Batalha Naval\n1 - Jogar\n2 - Sobre\n3 - Sair\nEscolha uma opção e pressione ENTER: ");
        
        while (!keyhit());
        opcao = readch() - '0';

        switch(opcao) {
            case 1:
                printf("Qual seu nome? ");
                while (1) {
                    while (!keyhit());
                    char c = readch();
                    if (c == '\n' || c == '\r') break;
                    nomeJogador[index++] = c;
                }
                nomeJogador[index] = '\0';  // Finaliza a string
                jogo(nomeJogador);
                break;
            case 2:
                printf("Informações do jogo\n");
                break;
            case 3:
                printf("Até mais!\n");
                break;
        }
    }
}

int main() {
    srand((unsigned)time(NULL));
    keyboardInit();
    menuInicial();
    keyboardDestroy();
    return 0;
}