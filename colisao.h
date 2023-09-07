#include "C:\raylib\raylib\src\raylib.h"
#include "capivara.h"
#include "salas.h"

void fixCollision(Capivara *capivara, Sala *sala){

    bool collision = 0;
    bool collisionX = 0;
    bool collisionY = 0;
    Rectangle prevX = {capivara->prevPos.x, capivara->pos.y, capivara->hitbox.width, capivara->hitbox.height};
    Rectangle prevY = {capivara->pos.x, capivara->prevPos.y, capivara->hitbox.width, capivara->hitbox.height};

    // paredes
    for (int i = 0; i < 8; i++){

        collision  = CheckCollisionRecs(sala->paredes[i], capivara->hitbox);
        collisionX = CheckCollisionRecs(sala->paredes[i], prevX);
        collisionY = CheckCollisionRecs(sala->paredes[i], prevY);
        
        if (collision && !collisionX && collisionY){
            capivara->pos.x = capivara->prevPos.x;
            capivara->hitbox.x = capivara->pos.x;
        }
        if (collision && collisionX && !collisionY){
            capivara->pos.y = capivara->prevPos.y;
            capivara->hitbox.y = capivara->pos.y;
        }
        
    }

    // portas
    for (int i = 0; i < 4; i++){

        if (sala->porta[i].aberta == 0){

            collision = CheckCollisionRecs(sala->porta[i].hitbox, capivara->hitbox);
            collisionX = CheckCollisionRecs(sala->porta[i].hitbox, prevX);
            collisionY = CheckCollisionRecs(sala->porta[i].hitbox, prevY);
            
            if (collision && !collisionX && collisionY){
                capivara->pos.x = capivara->prevPos.x;
                capivara->hitbox.x = capivara->pos.x;
            }
            if (collision && collisionX && !collisionY){
                capivara->pos.y = capivara->prevPos.y;
                capivara->hitbox.y = capivara->pos.y;
            }
        }
    }
}

void updateRoom(Capivara *capivara, Sala *sala){

    bool collision = 0;

    for (int i = 0; i < 4; i++){

        collision = CheckCollisionRecs(sala->saida[i].hitbox, capivara->hitbox);

        if (collision){
            
            if (i == cima){
                capivara->pos.y += 9*square;
                capivara->hitbox.y = capivara->pos.y;

                capivara->salaAtual = sala->saida[i].saidaPara;
            }
            if (i == esquerda){
                capivara->pos.x += 11*square;
                capivara->hitbox.x = capivara->pos.x;                    
            
                capivara->salaAtual = sala->saida[i].saidaPara;
            }
            if (i == direita){
                capivara->pos.x -= 11*square;
                capivara->hitbox.x = capivara->pos.x;

                capivara->salaAtual = sala->saida[i].saidaPara;
            }
            if (i == baixo){
                capivara->pos.y -= 9*square;
                capivara->hitbox.y = capivara->pos.y;

                capivara->salaAtual = sala->saida[i].saidaPara;
            }
        }
    }
}