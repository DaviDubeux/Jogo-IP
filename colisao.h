#include "C:\raylib\raylib\src\raylib.h"
#include "capivara.h"
#include "salas.h"

void fixCollision(Capivara *capivara, Sala *sala){

    bool collision;
    bool collisionX;
    bool collisionY;
    int salaAtual = capivara->salaAtual;
    Rectangle prevX = {capivara->prevPos.x, capivara->pos.y, capivara->hitbox.width, capivara->hitbox.height};
    Rectangle prevY = {capivara->pos.x, capivara->prevPos.y, capivara->hitbox.width, capivara->hitbox.height};

    // paredes
    for (int i = 0; i < 8; i++){

        collision  = CheckCollisionRecs(sala->paredes[i], capivara->hitbox);
        collisionX = CheckCollisionRecs(sala->paredes[i], prevX);
        collisionY = CheckCollisionRecs(sala->paredes[i], prevY);
        
        if (collision && !collisionX){
            capivara->pos.x = capivara->prevPos.x;
            capivara->hitbox.x = capivara->pos.x; capivara->hitbox.y = capivara->pos.y;
        }
        if (collision && !collisionY){
            capivara->pos.y = capivara->prevPos.y;
            capivara->hitbox.x = capivara->pos.x; capivara->hitbox.y = capivara->pos.y;
        }
        
    }

    // portas
    for (int i = 0; i < 4; i++){
        collision = CheckCollisionRecs(sala[salaAtual].portas[i].hitbox, capivara->hitbox);
        if (collision && sala[salaAtual].portas[i].aberta == 0){
            collision  = CheckCollisionRecs(sala->paredes[i], capivara->hitbox);
            collisionX = CheckCollisionRecs(sala->paredes[i], prevX);
            collisionY = CheckCollisionRecs(sala->paredes[i], prevY);
            
            if (collision && !collisionX){
                capivara->pos.x = capivara->prevPos.x;
                capivara->hitbox.x = capivara->pos.x; capivara->hitbox.y = capivara->pos.y;
            }
            if (collision && !collisionY){
                capivara->pos.y = capivara->prevPos.y;
                capivara->hitbox.x = capivara->pos.x; capivara->hitbox.y = capivara->pos.y;
            }
        }
    }
}