#ifndef CAPIVARA
#define CAPIVARA
#include "C:\raylib\raylib\src\raylib.h"

typedef struct{

    int vida;
    int defesa;
    int ataque;
    int upgrades; // 0 - nada; 1 - cágado; 2 - aranha; 3 - galinha;
    int direcao; // 0 - L;   1 - NE;   2 - N;   3 - NO;   4 - O;   5 - SO;   6 - S;   7 - SE;
    Vector2 pos;
    Rectangle hitbox;
    Texture2D spriteCapivara[4][6];
    Texture2D spriteAtual;
    
} Capivara;
    
void loadCapivara(Capivara *capivara, const float screenW, const float screenH){};

#endif