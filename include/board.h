#ifndef BOARD_H
#define BOARD_H

void iniciaTabuleiro(char tabuleiro[10][10], char mascara[10][10]);
void exibeTabuleiro(char tabuleiro[10][10], char mascara[10][10], int mostraGabarito);
void posicionaBarcos(char tabuleiro[10][10]);
void verificaTiro(char tabuleiro[10][10], int linha, int coluna, int *pontos, char *mensagem);

#endif // BOARD_H