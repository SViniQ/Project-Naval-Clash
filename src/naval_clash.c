#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "screen.h"  
#include "keyboard.h"
#include "timer.h"

void menuInicial();
void iniciaTabuleiro(char tabuleiro[10][10], char mascara[10][10]);
void exibeMapa();
void exibeTabuleiro(char tabuleiro[10][10], char mascara[10][10], int mostraGabarito);
void posicionaBarcos(char tabuleiro[10][10]);
void verificaTiro(char tabuleiro[10][10], int linha, int coluna, int *pontos, char *mensagem);
void jogo(char nomeJogador[50]);

void limpaTela() {
    screenClear();  // Limpa a tela usando a função do screen.c
}

void iniciaTabuleiro(char tabuleiro[10][10], char mascara[10][10]) {
    for (int linha = 0; linha < 10; linha++) {
        for (int coluna = 0; coluna < 10; coluna++) {
            tabuleiro[linha][coluna] = 'A';
            mascara[linha][coluna] = '*';
        }
    }
}

void exibeMapa() {

    screenGotoxy(3, 2);
    printf("     ");
    for (int cont = 0; cont < 10; cont++) {
        printf("%d ", cont);
    }
    screenGotoxy(3, 3);
    printf("     ");
    for (int cont = 0; cont < 10; cont++) {
        printf("| ");  // Delimitador visual para as colunas
    }
    printf("\n");
}

void exibeTabuleiro(char tabuleiro[10][10], char mascara[10][10], int mostraGabarito) {
    for (int linha = 0; linha < 10; linha++) {
        screenGotoxy(3, linha + 5);
        printf("%d - ", linha);

        for (int coluna = 0; coluna < 10; coluna++) {
            if (mascara[linha][coluna] == 'A')
                screenSetColor(BLUE, BLACK);   // Água em azul
            else if (mascara[linha][coluna] == 'P')
                screenSetColor(GREEN, BLACK);  // Barcos em verde
            else
                screenSetColor(WHITE, BLACK);  // Outros elementos

            printf(" %c", mascara[linha][coluna]);
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


int main() {
    atexit(keyboardDestroy);
    srand((unsigned)time(NULL));
    screenInit(0);
    menuInicial(); 
    screenDestroy();  
    return 0;
}

