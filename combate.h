#ifndef COMBATE
#define COMBATE
#include <stdio.h>
#include <stdlib.h>
#include "C:\raylib\raylib\src\raylib.h"
#include "personagens.h"
#define square 96.0f

typedef struct{
    float width;
    float height;
    Vector2 frame;
    Texture2D textura;
    Rectangle statsFrame;
    Vector2 nomeFrame;
    Vector2 vidaFrame;
}Info;

typedef struct{
    float width;
    float height;
    Vector2 frame;
    Info capivaraInfo;
    Info bossInfo;
    Texture2D textura;
}Arena;

void loadArena(Arena *arena, const float screenW, const float screenH){
    arena->width = 12*square;
    arena->height = 10*square;
    arena->frame = (Vector2){(screenW/2.0f) - ((arena->width)/2.0f),
                             (screenH/2.0f) - ((arena->height)/2.0f)};
    arena->capivaraInfo.frame = (Vector2){arena->frame.x + 1*square, arena->frame.y + 4*square};
    arena->capivaraInfo.width =  4*square;
    arena->capivaraInfo.height = 3*square;
    //arena->capivaraInfo.capivaraSprite = LoadTexture("./assets/capivaraCombate.png");
    arena->capivaraInfo.statsFrame = (Rectangle){arena->frame.x + 5*square, arena->frame.y + 5*square, 5*square, 2*square};
    arena->capivaraInfo.nomeFrame = (Vector2){arena->frame.x + 5.5*square, arena->frame.y + 5.5*square};
    arena->capivaraInfo.vidaFrame = (Vector2){arena->frame.x + 6.5*square, arena->frame.y + 6.5*square};


    arena->bossInfo.frame = (Vector2){arena->frame.x + 7*square, arena->frame.y + 1*square};
    arena->bossInfo.width = 4*square;
    arena->bossInfo.height = 3*square;
    //arena->bossInfo.capivaraSprite = LoadTexture("./assets/capivaraCombate.png");
    arena->bossInfo.statsFrame = (Rectangle){arena->frame.x + 2*square, arena->frame.y + 1*square, 5*square, 2*square};
    arena->bossInfo.nomeFrame = (Vector2){arena->frame.x + 2.5*square, arena->frame.y + 1.5*square};
    arena->bossInfo.vidaFrame = (Vector2){arena->frame.x + 3.5*square, arena->frame.y + 2.5*square};
}

void unloadArena(Arena *arena){

}

#endif