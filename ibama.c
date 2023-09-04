#include "ibama.h"

LoadIbama(Ibama *ibama){
    
    ibama->vida = 20;
    ibama->defesa = 20;
    ibama->ataque = 20;
    ibama->upgrades = 0;
    ibama->direcao = 6;
    ibama->pos.x = 10.0f;
    ibama->pos.y = 10.0f;
    ibama->hitbox = (Rectangle) {ibama->pos.x, ibama->pos.y, 0, 0};
    ibama->spriteIbama[0][0] = LoadTexture("./assets/icon_dd_final.jpg");


}