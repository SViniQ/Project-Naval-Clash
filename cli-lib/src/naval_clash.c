#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "screen.h"  // Incluímos o screen.h para usar as funções de interface

// Cabeçalhos de funções
void menuInicial();
void limpaTela();
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
            tabuleiro[linha][coluna] = 'A';   // Representa água
            mascara[linha][coluna] = '*';     // Máscara oculta
        }
    }
}

void exibeMapa() {
    
    // Desenhamos bordas em torno do mapa usando screenDrawBorders
    screenDrawBorders();
    
    // Cabeçalho do mapa
    screenGotoxy(5, 2);
    printf("     ");
    for (int cont = 0; cont < 10; cont++) {
        printf("%d ", cont);  // Cabeçalho das colunas (0-9)
    }
    screenGotoxy(5, 3);
    printf("     ");
    for (int cont = 0; cont < 10; cont++) {
        printf("| ");  // Delimitador visual para as colunas
    }
    printf("\n");
}

void exibeTabuleiro(char tabuleiro[10][10], char mascara[10][10], int mostraGabarito) {
    for (int linha = 0; linha < 10; linha++) {
        screenGotoxy(5, linha + 5);  // Posiciona a impressão das linhas a partir de (5, 5)
        printf("%d - ", linha);      // Exibe o número da linha

        for (int coluna = 0; coluna < 10; coluna++) {
            if (mascara[linha][coluna] == 'A')
                screenSetColor(BLUE, BLACK);   // Água em azul
            else if (mascara[linha][coluna] == 'P')
                screenSetColor(GREEN, BLACK);  // Barcos em verde
            else
                screenSetColor(WHITE, BLACK);  // Outros elementos

            printf(" %c", mascara[linha][coluna]);  // Exibe o conteúdo da máscara
            screenSetColor(WHITE, BLACK);          // Restaura a cor padrão
        }
        printf("\n");
    }

    if (mostraGabarito) {
        screenGotoxy(5, 17);  // Posiciona o gabarito na parte inferior da tela
        printf("Gabarito:\n");
        for (int linha = 0; linha < 10; linha++) {
            screenGotoxy(5, linha + 18);
            for (int coluna = 0; coluna < 10; coluna++) {
                printf(" %c", tabuleiro[linha][coluna]);
            }
            printf("\n");
        }
    }
}

void posicionaBarcos(char tabuleiro[10][10]) {
    int barcosPosicionados = 0;
    while (barcosPosicionados < 10) {
        int linha = rand() % 10;
        int coluna = rand() % 10;
        if (tabuleiro[linha][coluna] == 'A') {
            tabuleiro[linha][coluna] = 'P';  // Define a posição do barco
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

void informacoesjogo(){
    int opcao;
    while (!opcao == 0) {
        
        screenGotoxy(5, 3);
        printf("====|Informações do jogo|====");
        screenGotoxy(5, 5);
        printf("O jogo de batalha naval é um jogo de tabuleiro, no qual os");
        screenGotoxy(5, 6);
        printf("jogador tem de adivinhar em quais quadrados estão os navi-");
        screenGotoxy(5, 7);
        printf("os do oponente. O objetivo do jogo é afundar todos os nav-");
        screenGotoxy(5, 8);
        printf("ios do oponente. O jogo é em um tabuleiro de 10x10, onde");
        screenGotoxy(5, 9);
        printf("seu objetivo é afundar os barcos.");
        screenGotoxy(5, 11);
        printf("====|Regras de Tiro|====");
        screenGotoxy(5, 13);
        printf("- Você tem 10 tiros para acertar os navios.");
        screenGotoxy(5, 15);
        printf("====|Pontuação|====");
        screenGotoxy(5, 17);
        printf("- Cada acerto vale 10 pontos.");
        screenGotoxy(5, 18);
        printf("- Cada erro vale 0 pontos.");
        screenGotoxy(5, 20);
        printf("Boa Caçada!");
        screenGotoxy(5, 22);
        printf("Pressione 0 para voltar ao menu inicial: ");
        scanf("%d", &opcao);
    }
    menuInicial();
}

void jogo(char nomeJogador[50]) {
    char tabuleiro[10][10], mascara[10][10];
    int pontos = 0, tentativas = 0, maximoTentativas = 1;
    char mensagem[100] = "Bem-vindo ao jogo!";

    iniciaTabuleiro(tabuleiro, mascara);
    posicionaBarcos(tabuleiro);

    while (tentativas < maximoTentativas) {
        limpaTela();
        exibeMapa();
        exibeTabuleiro(tabuleiro, mascara, 0);

        // Exibe pontuação e tentativas restantes
        screenGotoxy(5, 16);
        printf("Pontos: %d, Tentativas Restantes: %d", pontos, maximoTentativas - tentativas);
        screenGotoxy(5, 17);
        printf("%s\n", mensagem);

        // Solicita a jogada
        int linhaJogada, colunaJogada;
        screenGotoxy(5, 19);
        printf("%s, digite uma linha: ", nomeJogador);
        scanf("%d", &linhaJogada);
        screenGotoxy(5, 20);
        printf("%s, digite uma coluna: ", nomeJogador);
        scanf("%d", &colunaJogada);

        // Verifica a jogada
        if (linhaJogada >= 0 && linhaJogada < 10 && colunaJogada >= 0 && colunaJogada < 10) {
            verificaTiro(tabuleiro, linhaJogada, colunaJogada, &pontos, mensagem);
            mascara[linhaJogada][colunaJogada] = tabuleiro[linhaJogada][colunaJogada];
            tentativas++;
        } else {
            printf("Posição inválida. Tente novamente.\n");
        }
    }

    // Finaliza o jogo e exibe opções de menu
    screenGotoxy(5, 22);
    printf("Fim de jogo!");
    screenGotoxy(5, 23);
    printf("Pontuação final: %d", pontos);
    screenGotoxy(5, 25);
    printf("1-Jogar Novamente");
    screenGotoxy(5, 26);
    printf("2-Ir para o Menu");
    screenGotoxy(5, 27);
    printf("3-Sair");
    screenGotoxy(5, 29);
    printf("Escolha uma opção e pressione ENTER: ");
    
    int opcao;
    scanf("%d", &opcao);
    switch(opcao) {
        case 1:
            limpaTela();
            screenDrawBorders();
            screenGotoxy(5, 3);
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

    while (opcao < 1 || opcao > 3) {
        limpaTela();
        screenDrawBorders();
        screenGotoxy(4, 3); // Posiciona o cursor na coluna 5 e linha 3
        printf("Bem-vindo ao Jogo de Batalha Naval!");
        screenGotoxy(4, 5); // Posiciona o cursor na coluna 5 e linha 5
        printf("1 - Jogar");
        screenGotoxy(4, 6); // Posiciona o cursor na coluna 5 e linha 6
        printf("2 - Sobre");
        screenGotoxy(4, 7); // Posiciona o cursor na coluna 5 e linha 7
        printf("3 - Sair");
        screenGotoxy(4, 9); // Posiciona o cursor na coluna 5 e linha 9
        printf("Escolha uma opção e pressione ENTER: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                limpaTela();
                screenDrawBorders();
                screenGotoxy(5, 3);
                printf("Qual seu nome? ");
                scanf("%s", nomeJogador);
                jogo(nomeJogador);
                break;
            case 2:
                limpaTela();
                screenDrawBorders();
                screenGotoxy(5, 3);
                informacoesjogo();
                break;
            case 3:
                printf("Até mais!\n");
                break;
        }
    }
}

int main() {
    srand((unsigned)time(NULL));
    screenInit(1);  // Inicializa a tela com bordas
    menuInicial();
    screenDestroy();  // Restaura o estado do terminal ao finalizar o programa
    return 0;
}
