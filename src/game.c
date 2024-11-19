#include "board.h"
#include "keyboard.h"
#include "screen.h"
#include "game.h"
#include "map.h"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>  
#include <string.h>

void jogo(char nomeJogador[50]) {
    char tabuleiro[10][10], mascara[10][10];
    int pontos = 0; 
    int tentativas = 0, maximoTentativas = 2;
    char mensagem[100] = "Bem-vindo ao jogo!";
    
    screenClear();
    iniciaTabuleiro(tabuleiro, mascara);
    posicionaBarcos(tabuleiro);

    screenDrawBorders();

    exibeMapa();
    while (tentativas < maximoTentativas) {
        exibeTabuleiro(tabuleiro, mascara, 0);

        screenGotoxy(3, 16);
        printf("Pontos: %d, Tentativas Restantes: %d", pontos, maximoTentativas - tentativas);
        screenGotoxy(3, 17);
        printf("%s\n", mensagem);

        int linhaJogada = -1, colunaJogada = -1;

        screenGotoxy(3, 19);
        printf("%s, digite uma linha (0-9): ", nomeJogador);
        scanf("%d", &linhaJogada);
        while (getchar() != '\n');

        screenGotoxy(3, 20);
        printf("%s, digite uma coluna (0-9): ", nomeJogador);
        scanf("%d", &colunaJogada);
        while (getchar() != '\n');  

        if (linhaJogada >= 0 && linhaJogada < 10 && colunaJogada >= 0 && colunaJogada < 10) {
            verificaTiro(tabuleiro, linhaJogada, colunaJogada, &pontos, mensagem);
            mascara[linhaJogada][colunaJogada] = tabuleiro[linhaJogada][colunaJogada];
            tentativas++;
        } else {
            strcpy(mensagem, "Posição inválida. Tente novamente.");
        }
    }

    screenGotoxy(3, 22);
    printf("Fim de jogo! Pontuação final: %d", pontos);
    screenGotoxy(3, 23);
    printf("1-Jogar Novamente");
    screenGotoxy(3, 24);
    printf("2-Ir para o Menu");
    screenGotoxy(3, 25);
    printf("3-Sair");
    keyboardInit();
    char opcao = getchar();
    keyboardDestroy();

    switch(opcao) {
        case '1':
            jogo(nomeJogador);
            break;
        case '2':
            menuInicial();
            break;
        case '3':
            printf("Até mais!\n");
            break;
        default:
            printf("Opção inválida. Saindo...\n");
    }
}