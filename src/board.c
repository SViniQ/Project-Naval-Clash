#include "board.h"
#include "screen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void iniciaTabuleiro(char tabuleiro[10][10], char mascara[10][10]) {
    for (int linha = 0; linha < 10; linha++) {
        for (int coluna = 0; coluna < 10; coluna++) {
            tabuleiro[linha][coluna] = 'A';
            mascara[linha][coluna] = '*';
        }
    }
}

void exibeTabuleiro(char tabuleiro[10][10], char mascara[10][10], int mostraGabarito) {
    for (int linha = 0; linha < 10; linha++) {
        screenGotoxy(3, linha + 5);
        printf("%d - ", linha);

        for (int coluna = 0; coluna < 10; coluna++) {
            if (mostraGabarito) {
                if (tabuleiro[linha][coluna] == 'A')
                    screenSetColor(BLUE, BLACK);
                else if (tabuleiro[linha][coluna] == 'P')
                    screenSetColor(GREEN, BLACK);
                else
                    screenSetColor(WHITE, BLACK);

                printf(" %c", tabuleiro[linha][coluna]);
            } else {
                if (mascara[linha][coluna] == 'A')
                    screenSetColor(BLUE, BLACK);
                else if (mascara[linha][coluna] == 'P')
                    screenSetColor(GREEN, BLACK);
                else
                    screenSetColor(WHITE, BLACK); 

                printf(" %c", mascara[linha][coluna]);
            }
            screenSetColor(WHITE, BLACK);
        }
        printf("\n");
    }
}

void posicionaBarcos(char tabuleiro[10][10]) {
    int barcosPosicionados = 0;
    while (barcosPosicionados < 10) {
        int linha = rand() % 10;
        int coluna = rand() % 10;
        if (tabuleiro[linha][coluna] == 'A') {
            tabuleiro[linha][coluna] = 'P';
            barcosPosicionados++;
        }
    }
}

void verificaTiro(char tabuleiro[10][10], int linha, int coluna, int *pontos, char *mensagem) {
    if (tabuleiro[linha][coluna] == 'P') {
        *pontos += 10;
        strcpy(mensagem, "Você acertou um barco pequeno! (10 pts)");
    } else {
        strcpy(mensagem, "Você acertou a água");
    }
}