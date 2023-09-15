#ifndef COLISAO
#define COLISAO
#include "C:\raylib\raylib\src\raylib.h"
#include "defines.h"

void fixCollision(Capivara *capivara, Sala *sala){

    bool collision = 0;
    bool collisionX = 0;
    bool collisionY = 0;
    Rectangle prevX = {capivara->prevHitbox.x, capivara->hitbox.y, capivara->hitbox.width, capivara->hitbox.height};
    Rectangle prevY = {capivara->hitbox.x, capivara->prevHitbox.y, capivara->hitbox.width, capivara->hitbox.height};

    // paredes
    for (int i = 0; i < 8; i++){

        collision  = CheckCollisionRecs(sala->paredes[i], capivara->hitbox);
        collisionX = CheckCollisionRecs(sala->paredes[i], prevX);
        collisionY = CheckCollisionRecs(sala->paredes[i], prevY);
        
        if (collision && !collisionX && collisionY){
            capivara->hitbox.x = capivara->prevHitbox.x;
            capivara->hitbox.x = capivara->hitbox.x;
            updateFrame(capivara);
        }
        if (collision && collisionX && !collisionY){
            capivara->hitbox.y = capivara->prevHitbox.y;
            capivara->hitbox.y = capivara->hitbox.y;
            updateFrame(capivara);
        }
        
    }

    // portas
    for (int i = 0; i < 4; i++){

        if (sala->porta[i].aberta == 0){

            collision = CheckCollisionRecs(sala->porta[i].hitbox, capivara->hitbox);
            collisionX = CheckCollisionRecs(sala->porta[i].hitbox, prevX);
            collisionY = CheckCollisionRecs(sala->porta[i].hitbox, prevY);
            
            if (collision && !collisionX && collisionY){
                capivara->hitbox.x = capivara->prevHitbox.x;
                capivara->hitbox.x = capivara->hitbox.x;
                updateFrame(capivara);
            }
            if (collision && collisionX && !collisionY){
                capivara->hitbox.y = capivara->prevHitbox.y;
                capivara->hitbox.y = capivara->hitbox.y;
                updateFrame(capivara);
            }
        }
    }

    // obstaculos
    for (int i = 0; i < sala->qtdObstaculos; i++){

        collision = CheckCollisionRecs(sala->obstaculo[i], capivara->hitbox);
        collisionX = CheckCollisionRecs(sala->obstaculo[i], prevX);
        collisionY = CheckCollisionRecs(sala->obstaculo[i], prevY);
        
        if (collision && !collisionX && collisionY){
            capivara->hitbox.x = capivara->prevHitbox.x;
            capivara->hitbox.x = capivara->hitbox.x;
            updateFrame(capivara);
        }
        if (collision && collisionX && !collisionY){
            capivara->hitbox.y = capivara->prevHitbox.y;
            capivara->hitbox.y = capivara->hitbox.y;
            updateFrame(capivara);
        }

    }

    // placa
    collision = CheckCollisionRecs(sala->placa.hitbox, capivara->hitbox);
    collisionX = CheckCollisionRecs(sala->placa.hitbox, prevX);
    collisionY = CheckCollisionRecs(sala->placa.hitbox, prevY);
    
    if (collision && !collisionX && collisionY){
        capivara->hitbox.x = capivara->prevHitbox.x;
        capivara->hitbox.x = capivara->hitbox.x;
        updateFrame(capivara);
    }
    if (collision && collisionX && !collisionY){
        capivara->hitbox.y = capivara->prevHitbox.y;
        capivara->hitbox.y = capivara->hitbox.y;
        updateFrame(capivara);
    }
}

void updateRoom(Capivara *capivara, Sala *sala){

    bool collision = 0;

    for (int i = 0; i < 4; i++){

        collision = CheckCollisionRecs(sala->saida[i].hitbox, capivara->hitbox);

        if (collision){
            
            if (i == cima){
                capivara->hitbox.y += 9*square;
                capivara->hitbox.y = capivara->hitbox.y;
                updateFrame(capivara);

                capivara->salaAtual = sala->saida[i].saidaPara;
            }
            if (i == esquerda){
                capivara->hitbox.x += 11*square;
                capivara->hitbox.x = capivara->hitbox.x;
                updateFrame(capivara);
            
                capivara->salaAtual = sala->saida[i].saidaPara;
            }
            if (i == direita){
                capivara->hitbox.x -= 11*square;
                capivara->hitbox.x = capivara->hitbox.x;
                updateFrame(capivara);

                capivara->salaAtual = sala->saida[i].saidaPara;
            }
            if (i == baixo){
                capivara->hitbox.y -= 9*square;
                capivara->hitbox.y = capivara->hitbox.y;
                updateFrame(capivara);

                capivara->salaAtual = sala->saida[i].saidaPara;
            }
        }
    }
}

void updateLendoPlaca(Capivara *capivara, Sala *sala, bool *pausado){
    if (capivara->interacao.interagindo){
        *pausado = CheckCollisionRecs(sala->placa.hitbox, capivara->interacao.hitbox);
    }
}

int updateBossfight(Capivara *capivara, Sala *sala){

    bool bossfight = 0;

    if (capivara->interacao.interagindo){

        if (capivara->salaAtual == salaCagado){
            bossfight = CheckCollisionRecs(sala->obstaculo[2], capivara->interacao.hitbox);
            if (bossfight && capivara->bossDerrotados == 0){ return combate; }
        }
        else if (capivara->salaAtual == salaAranhas){
            bossfight = CheckCollisionRecs(sala->obstaculo[6], capivara->interacao.hitbox);
            if (bossfight && capivara->bossDerrotados == 1){ return combate; }
        }
        else if (capivara->salaAtual == salaGalinha){
            bossfight = CheckCollisionRecs(sala->obstaculo[6], capivara->interacao.hitbox);
            if (bossfight && capivara->bossDerrotados == 2){ return combate; }
        }
        else if (capivara->salaAtual == salaPeixe){
            bossfight = CheckCollisionRecs(sala->obstaculo[1], capivara->interacao.hitbox);
            if (bossfight && capivara->bossDerrotados == 3){ return combate; }
        }
    }

    return explorando;
}

#endif