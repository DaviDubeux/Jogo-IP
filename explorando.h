#ifndef COLISAO
#define COLISAO
#include "C:\raylib\raylib\src\raylib.h"
#include "defines.h"

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

    // objetos
    for (int i = 0; i < sala->qtdObjetos; i++){

        collision = CheckCollisionRecs(sala->objeto[i].hitbox, capivara->hitbox);
        collisionX = CheckCollisionRecs(sala->objeto[i].hitbox, prevX);
        collisionY = CheckCollisionRecs(sala->objeto[i].hitbox, prevY);
        
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

void updatePorta(Capivara *capivara, Sala *sala){
    if (capivara->interacao.interagindo && capivara->temChave){
        if (capivara->chaves == 0 && capivara->salaAtual == salaHub && CheckCollisionRecs(sala->porta[esquerda].hitbox, capivara->interacao.hitbox)){
            sala->porta[esquerda].aberta = true; capivara->temChave = false;
        }
        if (capivara->chaves == 1 && capivara->salaAtual == salaHub && CheckCollisionRecs(sala->porta[direita].hitbox, capivara->interacao.hitbox)){
            sala->porta[direita].aberta = true; capivara->temChave = false;
        }
        if (capivara->chaves == 2 && capivara->salaAtual == salaHub && CheckCollisionRecs(sala->porta[cima].hitbox, capivara->interacao.hitbox)){
            sala->porta[cima].aberta = true; capivara->temChave = false;
        }
        if (capivara->chaves == 3 && capivara->salaAtual == salaGalinha && CheckCollisionRecs(sala->porta[cima].hitbox, capivara->interacao.hitbox)){
            sala->porta[cima].aberta = true; capivara->temChave = false;
        }
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

void updateLendo(Capivara *capivara, Sala *sala, bool *pausado, bool *lendoPlaca, bool *lendo){
    if (capivara->interacao.interagindo){
        for (int i = 0; i < sala->qtdObjetos && !(*lendo); i++){
            *pausado = CheckCollisionRecs(sala->objeto[i].hitbox, capivara->interacao.hitbox);
            *lendo = *pausado;
        }
        if (capivara->salaAtual == salaJardim){
            *lendoPlaca = CheckCollisionRecs(sala->objeto[7].hitbox, capivara->interacao.hitbox);
            if (capivara->chaves == 0 && (*lendoPlaca)){
                capivara->temChave = true;
            }
        }
    }
}

int updateBossfight(Capivara *capivara, Sala *sala, Music *musicaCombate){

    bool bossfight = 0;

    if (capivara->interacao.interagindo){

        if (capivara->salaAtual == salaCagado){
            bossfight = CheckCollisionRecs(sala->objeto[2].hitbox, capivara->interacao.hitbox);
            if (bossfight && capivara->bossDerrotados == 0){ return combate; }
        }
        else if (capivara->salaAtual == salaAranhas){
            bossfight = CheckCollisionRecs(sala->objeto[6].hitbox, capivara->interacao.hitbox);
            if (bossfight && capivara->bossDerrotados == 1){ return combate; }
        }
        else if (capivara->salaAtual == salaGalinha){
            bossfight = CheckCollisionRecs(sala->objeto[7].hitbox, capivara->interacao.hitbox);
            if (bossfight && capivara->bossDerrotados == 2){ return combate; }
        }
        else if (capivara->salaAtual == salaPeixe){
            bossfight = CheckCollisionRecs(sala->objeto[3].hitbox, capivara->interacao.hitbox);
            if (bossfight && capivara->bossDerrotados == 3){ return combate; }
        }
    }

    StopMusicStream(*musicaCombate);

    return explorando;
}

#endif