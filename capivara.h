#ifndef CAPIVARA
#define CAPIVARA
#include "C:\raylib\raylib\src\raylib.h"
#define square 96.0f

typedef struct{

    int vida;
    int defesa;
    int ataque;
    float speed;
    int upgrades; // 0 - nada; 1 - cágado; 2 - aranha; 3 - galinha;
    int direcao; // 0 - L;   1 - NE;   2 - N;   3 - NO;   4 - O;   5 - SO;   6 - S;   7 - SE;
    int salaAtual;
    Vector2 pos;
    Vector2 prevPos;
    Rectangle hitbox;
    Texture2D sprite;
    
} Capivara;
    
void loadCapivara(Capivara *capivara, const float screenW, const float screenH){
    
    capivara->vida = 20;
    capivara->defesa = 20;
    capivara->ataque = 20;
    capivara->speed = 400.0f;
    capivara->upgrades = 0;
    capivara->direcao = 6;
    capivara->salaAtual = 0;
    capivara->pos.x = screenW/2.0f - square/2;
    capivara->pos.y = screenH/2.0f - square/2;
    capivara->prevPos.x = screenW/2.0f - square/2;
    capivara->prevPos.y = screenH/2.0f - square/2;
    capivara->hitbox = (Rectangle) {capivara->pos.x, capivara->pos.y, square, square};
    capivara->sprite = LoadTexture("./assets/capivara.png");
    
}

#endif