#ifndef SALA
#define SALA
#include "C:\raylib\raylib\src\raylib.h"
#include <stdlib.h>
#define square 96.0f

enum {
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

enum{
    menu,        // menu = 0
    explorando,  // explorando = 1
    combate,     // combate = 2
    gameOver     // gameOver = 3
}Mode;


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
    Vector2 frame;
    Rectangle paredes[8];
    Porta porta[4]; //
    Saida saida[4]; //

    // específicos da sala
    int qtdObstaculos;
    Rectangle *obstaculo;
    Texture2D textura;

}Sala;

void loadSalas(Sala *sala, const float screenW, const float screenH){ // dá load em coisas em comuns das salas
    sala->width = 12*square; // em quadrados
    sala->height = 10*square; // em quadrados
    sala->frame = (Vector2){(screenW/2.0f) - ((sala->width)/2.0f),
                            (screenH/2.0f) - ((sala->height)/2.0f)};
    sala->paredes[0] = (Rectangle){sala->frame.x + square, sala->frame.y, 4*square, square};
    sala->paredes[1] = (Rectangle){sala->frame.x + 7*square, sala->frame.y, 4*square, square};
    sala->paredes[2] = (Rectangle){sala->frame.x, sala->frame.y + square, square, 3*square};
    sala->paredes[3] = (Rectangle){sala->frame.x + 11*square, sala->frame.y + square, square, 3*square};
    sala->paredes[4] = (Rectangle){sala->frame.x, sala->frame.y + 6*square, square, 3*square};
    sala->paredes[5] = (Rectangle){sala->frame.x + 11*square, sala->frame.y + 6*square, square, 3*square};
    sala->paredes[6] = (Rectangle){sala->frame.x + square, sala->frame.y + 9*square, 4*square, square};
    sala->paredes[7] = (Rectangle){sala->frame.x + 7*square, sala->frame.y + 9*square, 4*square, square};

    sala->porta[cima].hitbox = (Rectangle){sala->frame.x + 5*square, sala->frame.y, 2*square, square};
    sala->porta[esquerda].hitbox = (Rectangle){sala->frame.x, sala->frame.y + 4*square, square, 2*square};
    sala->porta[direita].hitbox = (Rectangle){sala->frame.x + 11*square, sala->frame.y + 4*square, square, 2*square};
    sala->porta[baixo].hitbox = (Rectangle){sala->frame.x + 5*square, sala->frame.y + 9*square, 2*square, square};

    sala->saida[cima].hitbox = (Rectangle){sala->frame.x + 5*square, sala->frame.y - square, 2*square, square};
    sala->saida[esquerda].hitbox = (Rectangle){sala->frame.x - square, sala->frame.y + 4*square, square, 2*square};
    sala->saida[direita].hitbox = (Rectangle){sala->frame.x + 12*square, sala->frame.y + 4*square, square, 2*square};
    sala->saida[baixo].hitbox = (Rectangle){sala->frame.x + 5*square, sala->frame.y + 10*square, 2*square, square};
}

void unloadSalas(Sala *sala){
    free(sala->obstaculo);
    UnloadTexture(sala->textura);
}

// jardim
void loadSala1(Sala *sala1){ // específicos da sala 1

    sala1->qtdObstaculos = 0;
    sala1->obstaculo = NULL;
    sala1->porta[cima].aberta = true;      sala1->saida[cima].saidaPara = salaHub;
    sala1->porta[esquerda].aberta = false; sala1->saida[esquerda].saidaPara = salaJardim;
    sala1->porta[direita].aberta = false;  sala1->saida[direita].saidaPara = salaJardim;
    sala1->porta[baixo].aberta = false;    sala1->saida[baixo].saidaPara = salaJardim;
    sala1->textura = LoadTexture("./assets/salaJardim.png");
    sala1->textura.width = 1152.0f;
    sala1->textura.height = 960.0f;
    
}

// hub
void loadSala2(Sala *sala2){
    sala2->qtdObstaculos = 4;
    sala2->obstaculo = (Rectangle *) malloc((sala2->qtdObstaculos)*sizeof(Rectangle));
    if (sala2->obstaculo == NULL){ return; }

    sala2->obstaculo[0] = (Rectangle){sala2->frame.x + 2*square, sala2->frame.y + 1*square, 2*square, 1*square};
    sala2->obstaculo[1] = (Rectangle){sala2->frame.x + 8*square, sala2->frame.y + 1*square, 2*square, 1*square};
    sala2->obstaculo[2] = (Rectangle){sala2->frame.x + 2*square, sala2->frame.y + 8*square, 1*square, 1*square};
    sala2->obstaculo[3] = (Rectangle){sala2->frame.x + 7*square, sala2->frame.y + 8*square, 3*square, 1*square};

    sala2->porta[cima].aberta = true;     sala2->saida[cima].saidaPara = salaGalinha;
    sala2->porta[esquerda].aberta = true; sala2->saida[esquerda].saidaPara = salaCagado;
    sala2->porta[direita].aberta = true;  sala2->saida[direita].saidaPara = salaAranhas;
    sala2->porta[baixo].aberta = true;    sala2->saida[baixo].saidaPara = salaJardim;
    sala2->textura = LoadTexture("./assets/salaHub.png");
    sala2->textura.width = 1152.0f;
    sala2->textura.height = 960.0f;
}

// cagado
void loadSala3(Sala *sala3){
    sala3->qtdObstaculos = 4;
    sala3->obstaculo = (Rectangle *) malloc((sala3->qtdObstaculos)*sizeof(Rectangle));
    if (sala3->obstaculo == NULL){ return; }

    sala3->obstaculo[0] = (Rectangle){sala3->frame.x + 7*square, sala3->frame.y + 1*square, 3*square, 1*square};
    sala3->obstaculo[1] = (Rectangle){sala3->frame.x + 1*square, sala3->frame.y + 3*square, 1*square, 4*square};
    sala3->obstaculo[2] = (Rectangle){sala3->frame.x + 4*square, sala3->frame.y + 3*square, 2*square, 4*square};
    sala3->obstaculo[3] = (Rectangle){sala3->frame.x + 2*square, sala3->frame.y + 4*square, 2*square, 2*square}; // sofá

    sala3->porta[cima].aberta = false;     sala3->saida[cima].saidaPara = salaCagado;
    sala3->porta[esquerda].aberta = false; sala3->saida[esquerda].saidaPara = salaCagado;
    sala3->porta[direita].aberta = true;   sala3->saida[direita].saidaPara = salaHub;
    sala3->porta[baixo].aberta = false;    sala3->saida[baixo].saidaPara = salaCagado;
    sala3->textura = LoadTexture("./assets/salaCagado.png");
    sala3->textura.width = 1152.0f;
    sala3->textura.height = 960.0f;
}

// aranhas
void loadSala4(Sala *sala4){
    sala4->qtdObstaculos = 8;
    sala4->obstaculo = (Rectangle *) malloc((sala4->qtdObstaculos)*sizeof(Rectangle));
    if (sala4->obstaculo == NULL){ return; }

    sala4->obstaculo[0] = (Rectangle){sala4->frame.x + 2*square, sala4->frame.y + 1*square, 2*square, 1*square};
    sala4->obstaculo[1] = (Rectangle){sala4->frame.x + 6*square, sala4->frame.y + 1*square, 2*square, 1*square};
    sala4->obstaculo[2] = (Rectangle){sala4->frame.x + 6*square, sala4->frame.y + 3*square, 2*square, 3*square};
    sala4->obstaculo[3] = (Rectangle){sala4->frame.x + 10*square, sala4->frame.y + 3*square, 1*square, 2*square};
    sala4->obstaculo[4] = (Rectangle){sala4->frame.x + 10*square, sala4->frame.y + 6*square, 1*square, 1*square};
    sala4->obstaculo[5] = (Rectangle){sala4->frame.x + 9*square, sala4->frame.y + 7*square, 2*square, 2*square};
    sala4->obstaculo[6] = (Rectangle){sala4->frame.x + 2*square, sala4->frame.y + 8*square, 1*square, 1*square};
    sala4->obstaculo[7] = (Rectangle){sala4->frame.x + 3*square, sala4->frame.y + 8*square, 1*square, 1*square};

    sala4->porta[cima].aberta = false;     sala4->saida[cima].saidaPara = salaAranhas;
    sala4->porta[esquerda].aberta = true;  sala4->saida[esquerda].saidaPara = salaHub;
    sala4->porta[direita].aberta = false;  sala4->saida[direita].saidaPara = salaAranhas;
    sala4->porta[baixo].aberta = false;    sala4->saida[baixo].saidaPara = salaAranhas;
    sala4->textura = LoadTexture("./assets/salaAranhas.png");
    sala4->textura.width = 1152.0f;
    sala4->textura.height = 960.0f;
}

// galinha
void loadSala5(Sala *sala5){
    sala5->qtdObstaculos = 0;
    sala5->obstaculo = NULL;
    sala5->porta[cima].aberta = true;      sala5->saida[cima].saidaPara = salaPeixe;
    sala5->porta[esquerda].aberta = false; sala5->saida[esquerda].saidaPara = salaGalinha;
    sala5->porta[direita].aberta = false;  sala5->saida[direita].saidaPara = salaGalinha;
    sala5->porta[baixo].aberta = true;     sala5->saida[baixo].saidaPara = salaHub;
    sala5->textura = LoadTexture("./assets/salaGalinha.png");
    sala5->textura.width = 1152.0f;
    sala5->textura.height = 960.0f;
}

// peixe
void loadSala6(Sala *sala6){
    sala6->qtdObstaculos = 0;
    sala6->obstaculo = NULL;
    sala6->porta[cima].aberta = false;     sala6->saida[cima].saidaPara = salaPeixe;
    sala6->porta[esquerda].aberta = false; sala6->saida[esquerda].saidaPara = salaPeixe;
    sala6->porta[direita].aberta = false;  sala6->saida[direita].saidaPara = salaPeixe;
    sala6->porta[baixo].aberta = true;    sala6->saida[baixo].saidaPara = salaGalinha;
    sala6->textura = LoadTexture("./assets/salaPeixe.png");
    sala6->textura.width = 1152.0f;
    sala6->textura.height = 960.0f;
}

#endif