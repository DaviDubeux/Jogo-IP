#include "capivara.h"

void loadCapivara(Capivara *capivara, const float screenW, const float screenH){
    
    capivara->vida = 20;
    capivara->defesa = 20;
    capivara->ataque = 20;
    capivara->upgrades = 0;
    capivara->direcao = 6;
    capivara->pos.x = 0.0f;
    capivara->pos.y = 100.0f;
    capivara->hitbox = (Rectangle) {capivara->pos.x, capivara->pos.y, 32, 32};
    // capivara->spriteAtual = LoadTexture("./assets/capivara.png");
    
}
