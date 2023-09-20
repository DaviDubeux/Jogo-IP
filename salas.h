#ifndef SALA
#define SALA
#include "C:\raylib\raylib\src\raylib.h"
#include <stdlib.h>
#include <string.h>
#include "defines.h"


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
    free(sala->objeto);
    UnloadTexture(sala->textura);
    for (int i = 0; i < 4; i++){
        UnloadTexture(sala->porta[i].textura);
    }
    UnloadMusicStream(sala->musica);
}

// jardim
void loadSala1(Sala *sala1){ // específicos da sala 1
    sala1->qtdObjetos = 9;
    
    sala1->objeto = (Objeto *) malloc((sala1->qtdObjetos)*sizeof(Objeto));
    if(sala1->objeto == NULL) { return;}

    sala1->objeto[0].hitbox = (Rectangle){sala1->frame.x + 3*square, sala1->frame.y + 1*square, 1*square, 1*square};
    sala1->objeto[0].mensagem[0] = '\0';
    strcpy(sala1->objeto[0].mensagem, "Pedra");

    sala1->objeto[1].hitbox = (Rectangle){sala1->frame.x + 8*square, sala1->frame.y + 1*square, 1*square, 1*square};
    sala1->objeto[1].mensagem[0] = '\0';
    strcpy(sala1->objeto[1].mensagem, "Mais uma Pedra");

    sala1->objeto[2].hitbox = (Rectangle){sala1->frame.x + 9*square, sala1->frame.y + 8*square, 1*square, 1*square};
    sala1->objeto[2].mensagem[0] = '\0';
    strcpy(sala1->objeto[2].mensagem, "É, eu não subo nela");

    sala1->objeto[3].hitbox = (Rectangle){sala1->frame.x + 3*square, sala1->frame.y + 4*square, 1*square, 1*square};
    sala1->objeto[3].mensagem[0] = '\0';
    strcpy(sala1->objeto[3].mensagem, "Outra Pedra");

    sala1->objeto[4].hitbox = (Rectangle){sala1->frame.x + 9*square, sala1->frame.y + 4*square, 1*square, 1*square};
    sala1->objeto[4].mensagem[0] = '\0';
    strcpy(sala1->objeto[4].mensagem, "Mais uma outra\nPedra");

    sala1->objeto[5].hitbox = (Rectangle){sala1->frame.x + 2*square, sala1->frame.y + 7*square, 1*square, 1*square};
    sala1->objeto[5].mensagem[0] = '\0';
    strcpy(sala1->objeto[5].mensagem, "Tem uma flor\naqui do lado");

    sala1->objeto[6].hitbox = (Rectangle){sala1->frame.x + 6*square, sala1->frame.y + 7*square, 1*square, 1*square};
    sala1->objeto[6].mensagem[0] = '\0';
    strcpy(sala1->objeto[6].mensagem, "Pedras né...");

    sala1->objeto[7].hitbox = (Rectangle){sala1->frame.x + 7*square, sala1->frame.y + 5*square, square, square};
    sala1->objeto[7].mensagem[0] = '\0';
    strcpy(sala1->objeto[7].mensagem, "Olá agente, sua missão aqui é simples: siga as\n pegadas no chão e resgate as 4 especies em \n extinção, mas cuidado, você não é o primeiro a ser\nconvocado para essa missão, muito cuidado!\n\nAqui está a lista de animais para encontrar,\nresgate-os, NESSA ORDEM,\n antes que seja tarde demais:\n\n*Tartaruga-de-pente\n*Aranha Caranguejeira\n*Cardeal-amarelo\n*Peixe beta\n Boa sorte\nDica: Cuidado com o sofá");

    sala1->objeto[8].hitbox = (Rectangle){sala1->frame.x + 10*square, sala1->frame.y + 1*square, 1*square, 1*square};
    sala1->objeto[8].mensagem[0] = '\0';
    strcpy(sala1->objeto[8].mensagem, "               RIP\n        Peixe Afogado");

    sala1->porta[cima].aberta = true; sala1->porta[cima].temTextura = false;
    sala1->saida[cima].saidaPara = salaHub;

    sala1->porta[esquerda].aberta = false; sala1->porta[esquerda].temTextura = false;
    sala1->saida[esquerda].saidaPara = salaJardim;

    sala1->porta[direita].aberta = false; sala1->porta[direita].temTextura = false;
    sala1->saida[direita].saidaPara = salaJardim;

    sala1->porta[baixo].aberta = false; sala1->porta[baixo].temTextura = false;
    sala1->saida[baixo].saidaPara = salaJardim;

    sala1->textura = LoadTexture("./assets/cenarios/explorando/salaJardim.png");
    sala1->textura.width = 1152.0f;
    sala1->textura.height = 960.0f;

    sala1->musica = LoadMusicStream("./assets/musicas/MusicaJardim.mp3");
    
}

// hub
void loadSala2(Sala *sala2){
    sala2->qtdObjetos = 5;
    sala2->objeto = (Objeto *) malloc((sala2->qtdObjetos)*sizeof(Objeto));
    if (sala2->objeto == NULL){ return; }

    sala2->objeto[0].hitbox = (Rectangle){sala2->frame.x + 2*square, sala2->frame.y + 1*square, 2*square, 1*square};
    sala2->objeto[0].mensagem[0] = '\0';
    strcpy(sala2->objeto[0].mensagem, "Um sofá suspeito");

    sala2->objeto[1].hitbox = (Rectangle){sala2->frame.x + 8*square, sala2->frame.y + 1*square, 2*square, 1*square};
    sala2->objeto[1].mensagem[0] = '\0';
    strcpy(sala2->objeto[1].mensagem, "Umas gavetas");

    sala2->objeto[2].hitbox = (Rectangle){sala2->frame.x + 10*square, sala2->frame.y + 1*square, 1*square, 1*square};
    sala2->objeto[2].mensagem[0] = '\0';
    strcpy(sala2->objeto[2].mensagem, "Plantas vivas");

    sala2->objeto[3].hitbox = (Rectangle){sala2->frame.x + 2*square, sala2->frame.y + 8*square, 1*square, 1*square};
    sala2->objeto[3].mensagem[0] = '\0';
    strcpy(sala2->objeto[3].mensagem, "Indícios que um cachorro\nfugiu dessa casa");

    sala2->objeto[4].hitbox = (Rectangle){sala2->frame.x + 7*square, sala2->frame.y + 8*square, 3*square, 1*square};
    sala2->objeto[4].mensagem[0] = '\0';
    strcpy(sala2->objeto[4].mensagem, "Livros aqui");

    sala2->porta[cima].aberta = false; sala2->porta[cima].temTextura = true;
    sala2->porta[cima].textura = LoadTexture("./assets/cenarios/explorando/portaGalinha.png");
    sala2->saida[cima].saidaPara = salaGalinha;

    sala2->porta[esquerda].aberta = false; sala2->porta[esquerda].temTextura = true;
    sala2->porta[esquerda].textura = LoadTexture("./assets/cenarios/explorando/portaCagado.png");
    sala2->saida[esquerda].saidaPara = salaCagado;

    sala2->porta[direita].aberta = false; sala2->porta[direita].temTextura = true;
    sala2->porta[direita].textura = LoadTexture("./assets/cenarios/explorando/portaAranhas.png");
    sala2->saida[direita].saidaPara = salaAranhas;

    sala2->porta[baixo].aberta = true; sala2->porta[baixo].temTextura = false;
    sala2->saida[baixo].saidaPara = salaJardim;

    sala2->textura = LoadTexture("./assets/cenarios/explorando/salaHub.png");
    sala2->textura.width = 1152.0f;
    sala2->textura.height = 960.0f;

    sala2->musica = LoadMusicStream("./assets/musicas/musicaCasa.mp3");
}

// cagado
void loadSala3(Sala *sala3){
    sala3->qtdObjetos = 6; 
    sala3->objeto = (Objeto *) malloc((sala3->qtdObjetos)*sizeof(Objeto));
    if (sala3->objeto == NULL){ return; }

    sala3->objeto[0].hitbox = (Rectangle){sala3->frame.x + 7*square, sala3->frame.y + 1*square, 3*square, 1*square};
    sala3->objeto[0].mensagem[0] = '\0';
    strcpy(sala3->objeto[0].mensagem, "...Por que tantas pedras?");

    sala3->objeto[1].hitbox = (Rectangle){sala3->frame.x + 1*square, sala3->frame.y + 3*square, 1*square, 4*square};
    sala3->objeto[1].mensagem[0] = '\0';
    strcpy(sala3->objeto[1].mensagem, "Nada para vasculhar aqui");

    sala3->objeto[2].hitbox = (Rectangle){sala3->frame.x + 4*square, sala3->frame.y + 3*square, 2*square, 4*square}; // sofá
    sala3->objeto[2].mensagem[0] = '\0';
    strcpy(sala3->objeto[2].mensagem, "Já derrotei esse sofá");

    sala3->objeto[3].hitbox = (Rectangle){sala3->frame.x + 2*square, sala3->frame.y + 4*square, 2*square, 2*square};
    sala3->objeto[3].mensagem[0] = '\0';
    strcpy(sala3->objeto[3].mensagem, "Uma mesa");

    sala3->objeto[4].hitbox = (Rectangle){sala3->frame.x + 5*square, sala3->frame.y + 9*square, 2*square, square};
    sala3->objeto[4].mensagem[0] = '\0';
    strcpy(sala3->objeto[4].mensagem, "Uma família reunida");

    sala3->objeto[5].hitbox = (Rectangle){sala3->frame.x + 8*square, sala3->frame.y + 9*square, 2*square, square};
    sala3->objeto[5].mensagem[0] = '\0';
    strcpy(sala3->objeto[5].mensagem, "Meu deus um peixe\nsendo engolido");


    sala3->porta[cima].aberta = false; sala3->porta[cima].temTextura = false;
    sala3->saida[cima].saidaPara = salaCagado;

    sala3->porta[esquerda].aberta = false; sala3->porta[esquerda].temTextura = false;
    sala3->saida[esquerda].saidaPara = salaCagado;
    
    sala3->porta[direita].aberta = true; sala3->porta[direita].temTextura = false;
    sala3->saida[direita].saidaPara = salaHub;

    sala3->porta[baixo].aberta = false; sala3->porta[baixo].temTextura = false;
    sala3->saida[baixo].saidaPara = salaCagado;

    sala3->textura = LoadTexture("./assets/cenarios/explorando/salaCagado.png");
    sala3->textura.width = 1152.0f;
    sala3->textura.height = 960.0f;

    sala3->musica = LoadMusicStream("./assets/musicas/musicaCasa.mp3");
}

// aranhas
void loadSala4(Sala *sala4){
    sala4->qtdObjetos = 8;
    sala4->objeto = (Objeto *) malloc((sala4->qtdObjetos)*sizeof(Objeto));
    if (sala4->objeto == NULL){ return; }

    sala4->objeto[0].hitbox = (Rectangle){sala4->frame.x + 2*square, sala4->frame.y + 1*square, 2*square, 1*square};
    sala4->objeto[0].mensagem[0] = '\0';
    strcpy(sala4->objeto[0].mensagem, "Elas foram torturadas?");

    sala4->objeto[1].hitbox = (Rectangle){sala4->frame.x + 6*square, sala4->frame.y + 1*square, 2*square, 1*square};
    sala4->objeto[1].mensagem[0] = '\0';
    strcpy(sala4->objeto[1].mensagem, "Eu não quero tomar banho");

    sala4->objeto[2].hitbox = (Rectangle){sala4->frame.x + 6*square, sala4->frame.y + 3*square, 2*square, 3*square};
    sala4->objeto[2].mensagem[0] = '\0';
    strcpy(sala4->objeto[2].mensagem, "Uma camisa de time");

    sala4->objeto[3].hitbox = (Rectangle){sala4->frame.x + 10*square, sala4->frame.y + 3*square, 1*square, 2*square};
    sala4->objeto[3].mensagem[0] = '\0';
    strcpy(sala4->objeto[3].mensagem, "Máquina de Lavar");

    sala4->objeto[4].hitbox = (Rectangle){sala4->frame.x + 10*square, sala4->frame.y + 6*square, 1*square, 1*square};
    sala4->objeto[4].mensagem[0] = '\0';
    strcpy(sala4->objeto[4].mensagem, "Roupas");

    sala4->objeto[5].hitbox = (Rectangle){sala4->frame.x + 9*square, sala4->frame.y + 7*square, 2*square, 2*square};
    sala4->objeto[5].mensagem[0] = '\0';
    strcpy(sala4->objeto[5].mensagem, "Nada encontrado");

    sala4->objeto[6].hitbox = (Rectangle){sala4->frame.x + 2*square, sala4->frame.y + 8*square, 1*square, 1*square}; // lixeira
    sala4->objeto[6].mensagem[0] = '\0';
    strcpy(sala4->objeto[6].mensagem, "Já salvei a aranha daqui");

    sala4->objeto[7].hitbox = (Rectangle){sala4->frame.x + 3*square, sala4->frame.y + 8*square, 1*square, 1*square};
    sala4->objeto[7].mensagem[0] = '\0';
    strcpy(sala4->objeto[7].mensagem, "Nada para vasculhar aqui");


    sala4->porta[cima].aberta = false; sala4->porta[cima].temTextura = false;
    sala4->saida[cima].saidaPara = salaAranhas;

    sala4->porta[esquerda].aberta = true; sala4->porta[esquerda].temTextura = false;
    sala4->saida[esquerda].saidaPara = salaHub;

    sala4->porta[direita].aberta = false; sala4->porta[direita].temTextura = false;
    sala4->saida[direita].saidaPara = salaAranhas;
    
    sala4->porta[baixo].aberta = false; sala4->porta[baixo].temTextura = false;
    sala4->saida[baixo].saidaPara = salaAranhas;

    sala4->textura = LoadTexture("./assets/cenarios/explorando/salaAranhas.png");
    sala4->textura.width = 1152.0f;
    sala4->textura.height = 960.0f;

    sala4->musica = LoadMusicStream("./assets/musicas/musicaCasa.mp3");
}

// galinha
void loadSala5(Sala *sala5){
    sala5->qtdObjetos = 9;
    sala5->objeto = (Objeto *) malloc((sala5->qtdObjetos)*sizeof(Objeto));
    if (sala5->objeto == NULL){ return; }

    sala5->objeto[0].hitbox = (Rectangle){sala5->frame.x + 1*square, sala5->frame.y + 1*square, 4*square, 1*square};
    sala5->objeto[0].mensagem[0] = '\0';
    strcpy(sala5->objeto[0].mensagem, "Um balcão de cozinha");

    sala5->objeto[1].hitbox = (Rectangle){sala5->frame.x + 1*square, sala5->frame.y + 2*square, 1*square, 3*square};
    sala5->objeto[1].mensagem[0] = '\0';
    strcpy(sala5->objeto[1].mensagem, "Um balcão de cozinha");

    sala5->objeto[2].hitbox = (Rectangle){sala5->frame.x + 8*square, sala5->frame.y + 1*square, 2*square, 1*square};
    sala5->objeto[2].mensagem[0] = '\0';
    strcpy(sala5->objeto[2].mensagem, "Um armário suspeito...");

    sala5->objeto[3].hitbox = (Rectangle){sala5->frame.x + 10*square, sala5->frame.y + 1*square, 1*square, 1*square};
    sala5->objeto[3].mensagem[0] = '\0';
    strcpy(sala5->objeto[3].mensagem, "Um vaso de plantas");

    sala5->objeto[4].hitbox = (Rectangle){sala5->frame.x + 3*square, sala5->frame.y + 3*square, 2*square, 2*square};
    sala5->objeto[4].mensagem[0] = '\0';
    strcpy(sala5->objeto[4].mensagem, "Uma mesa");

    sala5->objeto[5].hitbox = (Rectangle){sala5->frame.x + 7*square, sala5->frame.y + 4*square, 2*square, 3*square};
    sala5->objeto[5].mensagem[0] = '\0';
    strcpy(sala5->objeto[5].mensagem, "Outra mesa");

    sala5->objeto[6].hitbox = (Rectangle){sala5->frame.x + 1*square, sala5->frame.y + 5*square, 1*square, 2*square};
    sala5->objeto[6].mensagem[0] = '\0';
    strcpy(sala5->objeto[6].mensagem, "Duas geladeiras");

    sala5->objeto[7].hitbox = (Rectangle){sala5->frame.x + 1*square, sala5->frame.y + 7*square, 1*square, 1*square}; // forno
    sala5->objeto[7].mensagem[0] = '\0';
    strcpy(sala5->objeto[7].mensagem, "Já tirei a Galinha daí");

    sala5->objeto[8].hitbox = (Rectangle){sala5->frame.x + 8*square, sala5->frame.y + 8*square, 2*square, 1*square};
    sala5->objeto[8].mensagem[0] = '\0';
    strcpy(sala5->objeto[8].mensagem, "Isso vai para o meu\nrelatório");


    sala5->porta[cima].aberta = false; sala5->porta[cima].temTextura = true;
    sala5->porta[cima].textura = LoadTexture("./assets/cenarios/explorando/portaPeixe.png");
    sala5->saida[cima].saidaPara = salaPeixe;

    sala5->porta[esquerda].aberta = false; sala5->porta[esquerda].temTextura = false;
    sala5->saida[esquerda].saidaPara = salaGalinha;

    sala5->porta[direita].aberta = false; sala5->porta[direita].temTextura = false;
    sala5->saida[direita].saidaPara = salaGalinha;

    sala5->porta[baixo].aberta = true; sala5->porta[baixo].temTextura = false;
    sala5->saida[baixo].saidaPara = salaHub;

    sala5->textura = LoadTexture("./assets/cenarios/explorando/salaGalinha.png");
    sala5->textura.width = 1152.0f;
    sala5->textura.height = 960.0f;

    sala5->musica = LoadMusicStream("./assets/musicas/musicaCasa.mp3");
}

// peixe
void loadSala6(Sala *sala6){
    sala6->qtdObjetos = 8;
    sala6->objeto = (Objeto *) malloc((sala6->qtdObjetos)*sizeof(Objeto));
    if (sala6->objeto == NULL){ return; }


    sala6->objeto[0].hitbox = (Rectangle){sala6->frame.x + 3*square, sala6->frame.y + 1*square, 3*square, 1*square};
    sala6->objeto[0].mensagem[0] = '\0';
    strcpy(sala6->objeto[0].mensagem, "Roupas");

    sala6->objeto[1].hitbox = (Rectangle){sala6->frame.x + 6*square, sala6->frame.y + 1*square, 1*square, 1*square};
    sala6->objeto[1].mensagem[0] = '\0';
    strcpy(sala6->objeto[1].mensagem, "Uma cabeceira");

    sala6->objeto[2].hitbox = (Rectangle){sala6->frame.x + 7*square, sala6->frame.y + 1*square, 2*square, 4*square};
    sala6->objeto[2].mensagem[0] = '\0';
    strcpy(sala6->objeto[2].mensagem, "Uma cama");

    sala6->objeto[3].hitbox = (Rectangle){sala6->frame.x + 9*square, sala6->frame.y + 1*square, 2*square, 1*square}; // aquario
    sala6->objeto[3].mensagem[0] = '\0';
    strcpy(sala6->objeto[3].mensagem, "Já salvei o peixe de\nser comido vivo");

    sala6->objeto[4].hitbox = (Rectangle){sala6->frame.x + 1*square, sala6->frame.y + 3*square, 1*square, 3*square};
    sala6->objeto[4].mensagem[0] = '\0';
    strcpy(sala6->objeto[4].mensagem, "Será que chego lá voando?");

    sala6->objeto[5].hitbox = (Rectangle){sala6->frame.x + 2*square, sala6->frame.y + 4*square, 1*square, 1*square};
    sala6->objeto[5].mensagem[0] = '\0';
    strcpy(sala6->objeto[5].mensagem, "Anotando para o\nrelatório");

    sala6->objeto[6].hitbox = (Rectangle){sala6->frame.x + 10*square, sala6->frame.y + 5*square, 1*square, 3*square};
    sala6->objeto[6].mensagem[0] = '\0';
    strcpy(sala6->objeto[6].mensagem, "Trabalhando...");

    sala6->objeto[7].hitbox = (Rectangle){sala6->frame.x + 2*square, sala6->frame.y + 8*square, 3*square, 1*square};
    sala6->objeto[7].mensagem[0] = '\0';
    strcpy(sala6->objeto[7].mensagem, "O que diacho é isso?");


    sala6->porta[cima].aberta = false; sala6->porta[cima].temTextura = false;
    sala6->saida[cima].saidaPara = salaPeixe;

    sala6->porta[esquerda].aberta = false; sala6->porta[esquerda].temTextura = false;
    sala6->saida[esquerda].saidaPara = salaPeixe;

    sala6->porta[direita].aberta = false; sala6->porta[direita].temTextura = false;
    sala6->saida[direita].saidaPara = salaPeixe;

    sala6->porta[baixo].aberta = true; sala6->porta[baixo].temTextura = false;
    sala6->saida[baixo].saidaPara = salaGalinha;

    sala6->textura = LoadTexture("./assets/cenarios/explorando/salaPeixe.png");
    sala6->textura.width = 1152.0f;
    sala6->textura.height = 960.0f;

    sala6->musica = LoadMusicStream("./assets/musicas/musicaCasa.mp3");
}

#endif