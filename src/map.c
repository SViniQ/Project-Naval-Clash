#include "map.h"
#include "screen.h"
#include <stdio.h>


void exibeMapa() {

    screenGotoxy(3, 2);
    printf("     ");
    for (int cont = 0; cont < 10; cont++) {
        printf("%d ", cont);
    }
    screenGotoxy(3, 3);
    printf("     ");
    for (int cont = 0; cont < 10; cont++) {
        printf("| "); 
    }
    printf("\n");
}