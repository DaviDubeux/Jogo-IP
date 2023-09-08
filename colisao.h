#include "C:\raylib\raylib\src\raylib.h"
#include "capivara.h"
#include "salas.h"

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