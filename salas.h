#ifndef SALA
#define SALA
#include "C:\raylib\raylib\src\raylib.h"
#include <stdlib.h>
#include <string.h>
#include "defines.h"


void loadSalas(Sala *sala, const float screenW, const float screenH);

void unloadSalas(Sala *sala);

// jardim
void loadSala1(Sala *sala1);

// hub
void loadSala2(Sala *sala2);

// cagado
void loadSala3(Sala *sala3);

// aranhas
void loadSala4(Sala *sala4);

// galinha
void loadSala5(Sala *sala5);

// peixe
void loadSala6(Sala *sala6);


#endif