#include "C:\raylib\raylib\src\raylib.h"

#define WIDTH 1280
#define HEIGHT 720
#define square 32

typedef struct{

    Rectangle hitbox;
    Texture2D textura;

}Movel;

typedef struct{

    int height, width;
    int qtdMoveis;
    Movel *movel;
    int qtdSaidas;
    Rectangle *saida;
    Rectangle hitbox;
    Vector2 frame;
    Texture2D textura;

}Sala;

void loadSalas(Sala *sala[]){}