#ifndef COMBATE
#define COMBATE
#include <stdio.h>
#include <stdlib.h>
#include "C:\raylib\raylib\src\raylib.h"
#include "defines.h"

void loadArena(Arena *arena, const float screenW, const float screenH);

void unloadArena(Arena *arena);

void updateRound(int *round, Capivara *capivara, int* desenho_skin, int* desenho_skin_combate, int *gameMode, bool *pausado);


#endif