#ifndef SALA
#define SALA
#include "C:\raylib\raylib\src\raylib.h"

#define square 32

typedef struct{

    Rectangle hitbox;
    Texture2D textura;

}Movel;

typedef struct{

    float width, height;
    int qtdMoveis;
    Movel *movel;
    int qtdSaidas;
    Rectangle *saida;
    Rectangle hitbox;
    Vector2 pos;
    Texture2D textura;

}Sala;

void loadSala1(Sala *sala, const float screenW, const float screenH){};
void loadSala2(Sala *sala, const float screenW, const float screenH){};
void loadSala3(Sala *sala, const float screenW, const float screenH){};
void loadSala4(Sala *sala, const float screenW, const float screenH){};
void loadSala5(Sala *sala, const float screenW, const float screenH){};
void loadSala6(Sala *sala, const float screenW, const float screenH){};

#endif