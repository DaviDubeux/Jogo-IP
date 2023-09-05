#include "C:\raylib\raylib\src\raylib.h"
#include "salas.h"

void loadSala1(Sala *sala, const int screenW, const int screenH){
    sala->width = 12.0f; // em quadrados
    sala->height = 10.0f; // em quadrados
    sala->qtdMoveis = 0;
    sala->movel = NULL;
    sala->qtdSaidas = 0;
    sala->saida = NULL;
    sala->pos = (Vector2){(screenW/2.0f) - ((sala->width)*square/2.0f),
                            (screenH/2.0f) - ((sala->height)*square/2.0f)};

    sala->hitbox = (Rectangle){(screenW/2.0f) - ((sala->width - 4.0f)*square/2.0f),
                               (screenH/2.0f) - ((sala->height - 4.0f)*square/2.0f),
                               12.0f*square, 10.0f*square};
}