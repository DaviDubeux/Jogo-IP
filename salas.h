#ifndef SALA
#define SALA
#include "C:\raylib\raylib\src\raylib.h"
#define square 96.0f

enum {
    saidaFechada = -1,  // saidaFechada = -1
    salaJardim,         // salaJardim = 0
    salaHub,            // salaHub = 1
    salaCagado,         // salaCagado = 2
    salaAranhas,        // salaAranhas = 3
    salaGalinha,        // salaGalinha = 4
    salaPeixe           // salaPeixe = 5
}NumeroDasSalas;

enum {
    cima,         // cima = 0
    esquerda,     // esquerda = 1
    direita,      // direita = 2
    baixo,        // baixo = 3
}Direcao;

typedef struct{
    bool aberta;
    Rectangle hitbox;
}Porta;

typedef struct{
    int saidaPara;
    Rectangle hitbox;
}Saida;

typedef struct{

    // gerais de todas as salas
    float width;
    float height;
    Vector2 posImagem;
    Rectangle paredes[8];
    Porta porta[4]; //
    Saida saida[4]; //

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

    sala->porta[cima].hitbox = (Rectangle){sala->posImagem.x + 5*square, sala->posImagem.y, 2*square, square};
    sala->porta[esquerda].hitbox = (Rectangle){sala->posImagem.x, sala->posImagem.y + 4*square, square, 2*square};
    sala->porta[direita].hitbox = (Rectangle){sala->posImagem.x + 11*square, sala->posImagem.y + 4*square, square, 2*square};
    sala->porta[baixo].hitbox = (Rectangle){sala->posImagem.x + 5*square, sala->posImagem.y + 9*square, 2*square, square};

    sala->saida[cima].hitbox = (Rectangle){sala->posImagem.x + 5*square, sala->posImagem.y - square, 2*square, square};
    sala->saida[esquerda].hitbox = (Rectangle){sala->posImagem.x - square, sala->posImagem.y + 4*square, square, 2*square};
    sala->saida[direita].hitbox = (Rectangle){sala->posImagem.x + 12*square, sala->posImagem.y + 4*square, square, 2*square};
    sala->saida[baixo].hitbox = (Rectangle){sala->posImagem.x + 5*square, sala->posImagem.y + 10*square, 2*square, square};
}

// jardim
void loadSala1(Sala *sala1, const int screenW, const int screenH){ // específicos da sala 1

    sala1->qtdObstaculos = 0;
    sala1->obstaculo = NULL;
    sala1->porta[cima].aberta = true;     sala1->saida[cima].saidaPara = salaHub;
    sala1->porta[esquerda].aberta = false; sala1->saida[esquerda].saidaPara = saidaFechada;
    sala1->porta[direita].aberta = false;  sala1->saida[direita].saidaPara = saidaFechada;
    sala1->porta[baixo].aberta = false;    sala1->saida[baixo].saidaPara = saidaFechada;
    // sala1->textura = LoadTexture();
}

// hub
void loadSala2(Sala *sala2, const float screenW, const float screenH){
    sala2->qtdObstaculos = 0;
    sala2->obstaculo = NULL;
    sala2->porta[cima].aberta = true;     sala2->saida[cima].saidaPara = salaGalinha;
    sala2->porta[esquerda].aberta = true; sala2->saida[esquerda].saidaPara = salaCagado;
    sala2->porta[direita].aberta = true;  sala2->saida[direita].saidaPara = salaAranhas;
    sala2->porta[baixo].aberta = true;    sala2->saida[baixo].saidaPara = salaJardim;
    // sala2->textura = LoadTexture();
}

// cagado
void loadSala3(Sala *sala3, const float screenW, const float screenH){
    sala3->qtdObstaculos = 0;
    sala3->obstaculo = NULL;
    sala3->porta[cima].aberta = false;     sala3->saida[cima].saidaPara = saidaFechada;
    sala3->porta[esquerda].aberta = false; sala3->saida[esquerda].saidaPara = saidaFechada;
    sala3->porta[direita].aberta = true;  sala3->saida[direita].saidaPara = salaHub;
    sala3->porta[baixo].aberta = false;    sala3->saida[baixo].saidaPara = saidaFechada;
    // sala3->textura = LoadTexture();
}

// aranhas
void loadSala4(Sala *sala4, const float screenW, const float screenH){
    sala4->qtdObstaculos = 0;
    sala4->obstaculo = NULL;
    sala4->porta[cima].aberta = false;     sala4->saida[cima].saidaPara = saidaFechada;
    sala4->porta[esquerda].aberta = true; sala4->saida[esquerda].saidaPara = salaHub;
    sala4->porta[direita].aberta = false;  sala4->saida[direita].saidaPara = saidaFechada;
    sala4->porta[baixo].aberta = false;    sala4->saida[baixo].saidaPara = saidaFechada;
    // sala4->textura = LoadTexture();
}

// galinha
void loadSala5(Sala *sala5, const float screenW, const float screenH){
    sala5->qtdObstaculos = 0;
    sala5->obstaculo = NULL;
    sala5->porta[cima].aberta = true;     sala5->saida[cima].saidaPara = salaPeixe;
    sala5->porta[esquerda].aberta = false; sala5->saida[esquerda].saidaPara = saidaFechada;
    sala5->porta[direita].aberta = false;  sala5->saida[direita].saidaPara = saidaFechada;
    sala5->porta[baixo].aberta = true;    sala5->saida[baixo].saidaPara = salaHub;
    // sala5->textura = LoadTexture();
}

// peixe
void loadSala6(Sala *sala6, const float screenW, const float screenH){
    sala6->qtdObstaculos = 0;
    sala6->obstaculo = NULL;
    sala6->porta[cima].aberta = false;     sala6->saida[cima].saidaPara = saidaFechada;
    sala6->porta[esquerda].aberta = false; sala6->saida[esquerda].saidaPara = saidaFechada;
    sala6->porta[direita].aberta = false;  sala6->saida[direita].saidaPara = saidaFechada;
    sala6->porta[baixo].aberta = true;    sala6->saida[baixo].saidaPara = salaGalinha;
    // sala6->textura = LoadTexture();
}

#endif