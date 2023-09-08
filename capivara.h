#ifndef CAPIVARA
#define CAPIVARA
#include "C:\raylib\raylib\src\raylib.h"
#define square 96.0f

enum{
    sentidoCima = 1,     // sentidoCima = 1
    sentidoEsquerda, // sentidoEsquerda = 2
    sentidoDireita,  // sentidoDireita = 3
    sentidoBaixo     // sentidoBaixo = 4
}Sentido;

typedef struct{
    bool interagindo;
    Rectangle hitbox;
}Interacao;

typedef struct{

    int vida;
    int defesa;
    int ataque;
    float speed;
    int upgrades; // 0 - nada; 1 - cágado; 2 - aranha; 3 - galinha;
    int direcao; // 0 - L;   1 - NE;   2 - N;   3 - NO;   4 - O;   5 - SO;   6 - S;   7 - SE;
    int salaAtual;
    Vector2 frame;
    Rectangle hitbox;
    Rectangle prevHitbox;
    Interacao interacao;
    Texture2D sprite;
    
} Capivara;
    
void loadCapivara(Capivara *capivara, const float screenW, const float screenH){
    
    capivara->vida = 20;
    capivara->defesa = 20;
    capivara->ataque = 20;
    capivara->speed = 400.0f;
    capivara->upgrades = 0;
    capivara->direcao = 0;
    capivara->salaAtual = 0;
    capivara->frame.x = screenW/2.0f - square/2;
    capivara->frame.y = screenH/2.0f - square/2;
    capivara->hitbox = (Rectangle) {capivara->frame.x + 4.0f, capivara->frame.y + 4.0f, square - 8.0f, square - 8.0f};
    capivara->prevHitbox = capivara->hitbox;
    capivara->interacao.hitbox = (Rectangle) {capivara->hitbox.x, capivara->hitbox.y, square - 8.0f, square - 8.0f};
    capivara->interacao.interagindo = 0;
    capivara->sprite = LoadTexture("./assets/capivara.png");
    
}

void updateHitbox(Capivara *capivara){
    capivara->hitbox.x = capivara->frame.x + 4.0f;
    capivara->hitbox.y = capivara->frame.y + 4.0f;
}

void updateFrame(Capivara *capivara){
    capivara->frame.x = capivara->hitbox.x - 4.0f;
    capivara->frame.y = capivara->hitbox.y - 4.0f;
}

void updateInteracaoHitbox(Capivara *capivara){
    
    if (capivara->direcao == sentidoCima){
        capivara->interacao.hitbox.y = capivara->hitbox.y - square - 2.0f;
        capivara->interacao.hitbox.x = capivara->hitbox.x;
    }
    else if (capivara->direcao == sentidoBaixo){
        capivara->interacao.hitbox.y = capivara->hitbox.y + square + 2.0f;
        capivara->interacao.hitbox.x = capivara->hitbox.x;
    }
    else if (capivara->direcao == sentidoEsquerda){
        capivara->interacao.hitbox.y = capivara->hitbox.y;
        capivara->interacao.hitbox.x = capivara->hitbox.x - square - 2.0f;
    }
    else if (capivara->direcao == sentidoDireita){
        capivara->interacao.hitbox.y = capivara->hitbox.y;
        capivara->interacao.hitbox.x = capivara->hitbox.x + square + 2.0f;
    }

}


#endif