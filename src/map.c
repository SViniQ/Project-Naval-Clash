#include "map.h"
#include "screen.h"
#include "keyboard.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>  
#include <string.h>

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