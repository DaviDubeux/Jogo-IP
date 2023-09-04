#include "capivara.h"

loadCapivara(Capivara *capivara){
    
    capivara->vida = 20;
    capivara->defesa = 20;
    capivara->ataque = 20;
    capivara->upgrades = 0;
    capivara->direcao = 6;
    capivara->pos.x = -16.0f;
    capivara->pos.y = -16.0f;
    capivara->hitbox = (Rectangle) {capivara->pos.x, capivara->pos.y, 32, 32};
    capivara->spriteAtual = LoadTexture("./assets/seta.png");
    
}

mudaPos(Capivara *capivara){
    capivara->pos.x = 400;
    capivara->pos.y = 400;
}