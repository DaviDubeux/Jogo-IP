#ifndef PERSONAGENS
#define PERSONAGENS
#include "C:\raylib\raylib\src\raylib.h"
#include <string.h>
#include "defines.h"

void loadCapivaraExplorando(Capivara *capivara, const float screenW, const float screenH);

void loadCapivaraCombate(Capivara *capivara, Arena *arena);

void loadBoss1(Boss *boss);

void loadBoss2(Boss *boss);

void loadBoss3(Boss *boss);

void loadBoss4(Boss *boss);

//------------------------------

void loadAnimal1(Animal *animal);

void loadAnimal2(Animal *animal);

void loadAnimal3(Animal *animal);

void loadAnimal4(Animal *animal);
//------------------------------


#endif