#include "capivara.h"

loadCapivara(Capivara *capivara){
    
    capivara->vida = 20;
    capivara->defesa = 20;
    capivara->ataque = 20;
    capivara->upgrades = 0;
    capivara->direcao = 6;
    capivara->pos.x = 624;
    capivara->pos.y = 344;
    capivara->hitbox = (Rectangle) {capivara->pos.x, capivara->pos.y, 32, 32};
    
}
