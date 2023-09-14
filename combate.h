#ifndef COMBATE
#define COMBATE
#include <stdio.h>
#include <stdlib.h>
#include "C:\raylib\raylib\src\raylib.h"
#include "defines.h"

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
    arena->capivaraInfo.vidaFrame = (Vector2){arena->frame.x + 8.5*square, arena->frame.y + 6.5*square};


    arena->bossInfo.frame = (Vector2){arena->frame.x + 7*square, arena->frame.y + 1*square};
    arena->bossInfo.width = 4*square;
    arena->bossInfo.height = 3*square;
    //arena->bossInfo.capivaraSprite = LoadTexture("./assets/boss.png");
    arena->bossInfo.statsFrame = (Rectangle){arena->frame.x + 2*square, arena->frame.y + 1*square, 5*square, 2*square};
    arena->bossInfo.nomeFrame = (Vector2){arena->frame.x + 2.5*square, arena->frame.y + 1.5*square};
    arena->bossInfo.vidaFrame = (Vector2){arena->frame.x + 5.5*square, arena->frame.y + 2.5*square};

    arena->ataqueInfo = (Rectangle){arena->frame.x + 8.25*square, arena->frame.y + 7.25*square, 3.5*square, 2.5*square};

    arena->texturaEscolherAtaque = LoadTexture("./assets/arenaEscolherAtaque.png");
    arena->texturaDescricao = LoadTexture("./assets/arenaDescricao.png");
    arena->texturaEscolherAtaque.width = 1152.0f; arena->texturaEscolherAtaque.height = 960.0f;
    arena->texturaDescricao.width = 1152.0f; arena->texturaDescricao.height = 960.0f;
}

void unloadArena(Arena *arena){
    UnloadTexture(arena->texturaEscolherAtaque);
    UnloadTexture(arena->texturaDescricao);
    UnloadTexture(arena->capivaraInfo.textura);
    UnloadTexture(arena->bossInfo.textura);
}

void updateRound(int *round, Capivara *capivara, int* desenho_skin, int *gameMode){
    if (*round == mostrarAtaqueCapivara){ *round = escolherAtaqueBoss; }
    if (*round == mostrarAtaqueBoss){ *round = escolherAtaqueCapivara; }
    if (*round == escolheuErrado){ *round = escolherAtaqueCapivara; }
    if (*round == escolherAtaqueCapivara && capivara->vida <= 0){ *gameMode = gameOver; }
    if (*round == mostrarBossMorreu){
        capivara->vida = capivara->vidaMaxima;
            capivara->bossDerrotados++;
            //precisa ver quando fazer isso para depois de interagir com o animal
            *desenho_skin += 2*square;
            capivara->ataque[capivara->bossDerrotados].desbloqueado = true;
            for (int i = 0; i < 4; i++){ capivara->ataque[i].usos = capivara->ataque[i].usosMaximo; }
            *gameMode = explorando;
        }
}

#endif