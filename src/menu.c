#include "board.h"
#include "keyboard.h"
#include "screen.h"
#include "game.h"
#include "map.h"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>  
#include <string.h>

void menuInicial() {
    screenClear();
    screenDrawBorders();
    screenGotoxy(3, 3);
    printf("Bem-vindo ao Jogo de Batalha Naval!");
    screenGotoxy(3, 5);
    printf("1 - Jogar");
    screenGotoxy(3, 6);
    printf("2 - Sobre");
    screenGotoxy(3, 7);
    printf("3 - Sair");

    keyboardInit(); 
    char initialSettings = getchar();
    keyboardDestroy(); 

    switch(initialSettings) {
        case '1':
            char nomeJogador[50];
            screenGotoxy(3, 9);
            printf("Qual seu nome? ");
            scanf("%49s", nomeJogador);
            while (getchar() != '\n');  
            screenClear();
            screenDestroy(); 
            jogo(nomeJogador);
            break;
        case '2':
            screenClear();
            screenDrawBorders();
            screenGotoxy(3, 3);
            printf("===========================|Informações do jogo|===========================");
            screenGotoxy(3, 5);
            printf("O jogo de batalha naval é um jogo de tabuleiro, no qual os jogador tem de");
            screenGotoxy(3, 6);
            printf("adivinhar em quais quadrados estão os navios do oponente. O objetivo do ");
            screenGotoxy(3, 7);
            printf("jogo é afundar todos os navios do oponente. O jogo é em um tabuleiro de ");
            screenGotoxy(3, 8);
            printf("10x10, onde seu objetivo é afundar os barcos.");
            screenGotoxy(3, 10);
            printf("=============================|Regras de Tiro|==============================");
            screenGotoxy(3, 12);
            printf("- Você tem 10 tiros para acertar os navios.");
            screenGotoxy(3, 14);
            printf("===============================|Pontuação|=================================");
            screenGotoxy(3, 16);
            printf("- Cada acerto vale 10 pontos.");
            screenGotoxy(3, 17);
            printf("- Cada erro vale 0 pontos.");
            screenGotoxy(3, 19);
            printf("Boa Caçada!");
            screenGotoxy(3, 21);
            printf("Pressione 0 para voltar ao menu inicial: ");
            initialSettings = getchar(); 
                while (getchar() != '\n');
            menuInicial();
            break;
        case '3':
            printf("Até mais!\n");
            break;
        default:
            printf("Opção inválida. Saindo...\n");
    }
}
