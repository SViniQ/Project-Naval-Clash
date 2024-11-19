#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "screen.h"  
#include "keyboard.h"
#include "timer.h"
#include "board.h"
#include "map.h"
#include "game.h"


void limpaTela() {
    screenClear();  // Limpa a tela usando a função do screen.c
}


int main() {
    atexit(keyboardDestroy);
    srand((unsigned)time(NULL));
    screenInit(0);
    menuInicial(); 
    screenDestroy();  
    return 0;
}

