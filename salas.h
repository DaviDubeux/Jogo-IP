#ifndef SALA
#define SALA
#include "C:\raylib\raylib\src\raylib.h"
#define square 96.0f

typedef struct{
    Rectangle hitbox;
    bool aberta;
}Portas;

typedef struct{

    // gerais de todas as salas
    float width;
    float height;
    Vector2 posImagem;
    Rectangle paredes[8];
    Portas portas[4]; // 0 - cima; 1 - esquerda; 2 - direita; 3 - baixo
    Rectangle saidas[4]; // 0 - cima; 1 - esquerda; 2 - direita; 3 - baixo

    // específicos da sala
    int qtdObstaculos;
    Rectangle *obstaculo;
    Texture2D textura;

}Sala;

void loadSalas(Sala *sala, const int screenW, const int screenH){ // dá load em coisas em comuns das salas
    sala->width = 12.0f; // em quadrados
    sala->height = 10.0f; // em quadrados
    sala->posImagem = (Vector2){(screenW/2.0f) - ((sala->width)*square/2.0f),
                                (screenH/2.0f) - ((sala->height)*square/2.0f)};
    sala->paredes[0] = (Rectangle){sala->posImagem.x + square, sala->posImagem.y, 4*square, square};
    sala->paredes[1] = (Rectangle){sala->posImagem.x + 7*square, sala->posImagem.y, 4*square, square};
    sala->paredes[2] = (Rectangle){sala->posImagem.x, sala->posImagem.y + square, square, 3*square};
    sala->paredes[3] = (Rectangle){sala->posImagem.x + 11*square, sala->posImagem.y + square, square, 3*square};
    sala->paredes[4] = (Rectangle){sala->posImagem.x, sala->posImagem.y + 6*square, square, 3*square};
    sala->paredes[5] = (Rectangle){sala->posImagem.x + 11*square, sala->posImagem.y + 6*square, square, 3*square};
    sala->paredes[6] = (Rectangle){sala->posImagem.x + square, sala->posImagem.y + 9*square, 4*square, square};
    sala->paredes[7] = (Rectangle){sala->posImagem.x + 7*square, sala->posImagem.y + 9*square, 4*square, square};

    sala->portas[0].hitbox = (Rectangle){sala->posImagem.x + 5*square, sala->posImagem.y, 2*square, square};
    sala->portas[1].hitbox = (Rectangle){sala->posImagem.x, sala->posImagem.y + 4*square, square, 2*square};
    sala->portas[2].hitbox = (Rectangle){sala->posImagem.x + 11*square, sala->posImagem.y + 4*square, square, 2*square};
    sala->portas[3].hitbox = (Rectangle){sala->posImagem.x + 5*square, sala->posImagem.y + 9*square, 2*square, square};

    sala->saidas[0] = (Rectangle){sala->posImagem.x + 5*square, sala->posImagem.y - square, 2*square, square};
    sala->saidas[1] = (Rectangle){sala->posImagem.x - square, sala->posImagem.y + 4*square, square, 2*square};
    sala->saidas[2] = (Rectangle){sala->posImagem.x + 12*square, sala->posImagem.y + 4*square, square, 2*square};
    sala->saidas[3] = (Rectangle){sala->posImagem.x + 5*square, sala->posImagem.y + 10*square, 2*square, square};
}

// jardim
void loadSala1(Sala *sala1, const int screenW, const int screenH){ // específicos da sala 1

    sala1->qtdObstaculos = 0;
    sala1->obstaculo = NULL;
    sala1->portas[0].aberta = 1; sala1->portas[1].aberta = 0;
    sala1->portas[2].aberta = 0; sala1->portas[3].aberta = 0;
    // sala1->textura = LoadTexture();
}

// hub
void loadSala2(Sala *sala2, const float screenW, const float screenH){
    sala2->qtdObstaculos = 0;
    sala2->obstaculo = NULL;
    sala2->portas[0].aberta = 1; sala2->portas[1].aberta = 1;
    sala2->portas[2].aberta = 1; sala2->portas[3].aberta = 1;
    // sala2->textura = LoadTexture();
}

// cagado
void loadSala3(Sala *sala3, const float screenW, const float screenH){
    sala3->qtdObstaculos = 0;
    sala3->obstaculo = NULL;
    sala3->portas[0].aberta = 0; sala3->portas[1].aberta = 0;
    sala3->portas[2].aberta = 1; sala3->portas[3].aberta = 0;
    // sala3->textura = LoadTexture();
}

// aranhas
void loadSala4(Sala *sala4, const float screenW, const float screenH){
    sala4->qtdObstaculos = 0;
    sala4->obstaculo = NULL;
    sala4->portas[0].aberta = 0; sala4->portas[1].aberta = 1;
    sala4->portas[2].aberta = 0; sala4->portas[3].aberta = 0;
    // sala4->textura = LoadTexture();
}

// galinha
void loadSala5(Sala *sala5, const float screenW, const float screenH){
    sala5->qtdObstaculos = 0;
    sala5->obstaculo = NULL;
    sala5->portas[0].aberta = 1; sala5->portas[1].aberta = 0;
    sala5->portas[2].aberta = 0; sala5->portas[3].aberta = 1;
    // sala5->textura = LoadTexture();
}

// peixe
void loadSala6(Sala *sala6, const float screenW, const float screenH){
    sala6->qtdObstaculos = 0;
    sala6->obstaculo = NULL;
    sala6->portas[0].aberta = 0; sala6->portas[1].aberta = 0;
    sala6->portas[2].aberta = 0; sala6->portas[3].aberta = 1;
    // sala6->textura = LoadTexture();
}

#endif