#ifndef COLISAO
#define COLISAO
#include "C:\raylib\raylib\src\raylib.h"
#include "defines.h"

void updateHitbox(Capivara *capivara);

void updateFrame(Capivara *capivara);

void updateInteracaoHitbox(Capivara *capivara);

void fixCollision(Capivara *capivara, Sala *sala);

void updatePorta(Capivara *capivara, Sala *sala);

void updateRoom(Capivara *capivara, Sala *sala);

void updateLendo(Capivara *capivara, Sala *sala, bool *pausado, bool *lendoPlaca, bool *lendo);

int updateBossfight(Capivara *capivara, Sala *sala, Music *musicaCombate);

#endif