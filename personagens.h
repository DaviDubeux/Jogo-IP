#ifndef PERSONAGENS
#define PERSONAGENS
#include "C:\raylib\raylib\src\raylib.h"
#include <string.h>
#include "defines.h"

void loadCapivaraExplorando(Capivara *capivara, const float screenW, const float screenH){
    capivara->speed = 400.0f;
    capivara->direcao = 0;
    capivara->salaAtual = 0;
    capivara->temChave = false;
    capivara->chaves = 0;
    capivara->frame.x = screenW/2.0f - square/2;
    capivara->frame.y = screenH/2.0f - square/2;
    capivara->hitbox = (Rectangle) {capivara->frame.x + 4.0f, capivara->frame.y + 4.0f, square - 8.0f, square - 8.0f};
    capivara->prevHitbox = capivara->hitbox;
    capivara->interacao.hitbox = (Rectangle) {capivara->hitbox.x, capivara->hitbox.y, square - 8.0f, square - 8.0f};
    capivara->interacao.interagindo = 0;
    capivara->textura = LoadTexture("./assets/animais/capivara.png");
}

void loadCapivaraCombate(Capivara *capivara, Arena *arena){
    capivara->vida = 300;
    capivara->vidaMaxima = 300;
    capivara->bossDerrotados = 0;
    capivara->ataqueSelecionado = 0;
    capivara->texturaCombate = LoadTexture("./assets/animais/CombateCapivara.png");
    capivara->texturaCombate.width *= 3.0f; capivara->texturaCombate.height *= 3.0f;

    capivara->nome[0] = '\0';
    strcpy(capivara->nome, "Agente do ibama");

    capivara->ataque[0].dano = 40; capivara->ataque[0].chanceDeCritico = 0;
    capivara->ataque[0].usos = 20; capivara->ataque[0].usosMaximo = 20;
    capivara->ataque[0].desbloqueado = true;
    capivara->ataque[0].frame = (Vector2){arena->frame.x + 1.1*square, arena->frame.y + 7.2*square};
    capivara->ataque[0].width = 6*square; capivara->ataque[0].height = 0.75*square;
    capivara->ataque[0].nome[0] = '\0';
    strcpy(capivara->ataque[0].nome, "Canetada do Ibama");

    capivara->ataque[1].dano = 35; capivara->ataque[1].chanceDeCritico = 33;
    capivara->ataque[1].usos = 15; capivara->ataque[1].usosMaximo = 15;
    capivara->ataque[1].desbloqueado = false;
    capivara->ataque[1].frame = (Vector2){arena->frame.x + 1.1*square, arena->frame.y + 7.85*square};
    capivara->ataque[1].width = 6*square; capivara->ataque[1].height = 0.75*square;
    capivara->ataque[1].nome[0] = '\0';
    strcpy(capivara->ataque[1].nome, "Koopa troopa");

    capivara->ataque[2].dano = -65; capivara->ataque[2].chanceDeCritico = 0;
    capivara->ataque[2].usos = 15; capivara->ataque[2].usosMaximo = 15;
    capivara->ataque[2].desbloqueado = false;
    capivara->ataque[2].frame = (Vector2){arena->frame.x + 1.1*square, arena->frame.y + 8.5*square};
    capivara->ataque[2].width = 6*square; capivara->ataque[2].height = 0.75*square;
    capivara->ataque[2].nome[0] = '\0';
    strcpy(capivara->ataque[2].nome, "Bandaid de teia");

    capivara->ataque[3].dano = 60; capivara->ataque[3].chanceDeCritico = 40;
    capivara->ataque[3].usos = 10; capivara->ataque[3].usosMaximo = 10;
    capivara->ataque[3].desbloqueado = false;
    capivara->ataque[3].frame = (Vector2){arena->frame.x + 1.1*square, arena->frame.y + 9.2*square};
    capivara->ataque[3].width = 6*square; capivara->ataque[3].height = 0.75*square;
    capivara->ataque[3].nome[0] = '\0';
    strcpy(capivara->ataque[3].nome, "Pipoca com manteiga");
}

void loadBoss1(Boss *boss){
    boss->vida = 220;
    boss->vidaMaxima = 220;
    boss->textura = LoadTexture("./assets/boss/sofa.png");

    boss->nome[0] = '\0';
    strcpy(boss->nome, "Sofá de Thalya");
    
    boss->ataque[0].dano = 45;
    boss->ataque[0].nome[0] = '\0';
    strcpy(boss->ataque[0].nome, "Canhão de almofada");

    boss->ataque[1].dano = 40;
    boss->ataque[1].nome[1] = '\0';
    strcpy(boss->ataque[1].nome, "Esmagar");

    boss->ataque[2].dano = 30; boss->ataque[2].chanceDeCritico = 20;
    boss->ataque[2].nome[2] = '\0';
    strcpy(boss->ataque[2].nome, "Nuvem de ácaro");

    boss->ataque[3].dano = 35;
    boss->ataque[3].nome[3] = '\0';
    strcpy(boss->ataque[3].nome, "Braçada");
    
}

void loadBoss2(Boss *boss){
    boss->vida = 340;
    boss->vidaMaxima = 340;
    boss->textura = LoadTexture("./assets/boss/tiaDeThalya.png");

    boss->nome[0] = '\0';
    strcpy(boss->nome, "Tia de Thalya");
    
    boss->ataque[0].dano = 30;
    boss->ataque[0].nome[0] = '\0';
    strcpy(boss->ataque[0].nome, "Vassourada");

    boss->ataque[1].dano = 40; boss->ataque[1].chanceDeCritico = 20;
    boss->ataque[1].nome[1] = '\0';
    strcpy(boss->ataque[1].nome, "Havaianas Certeira");

    boss->ataque[2].dano = 35;
    boss->ataque[2].nome[2] = '\0';
    strcpy(boss->ataque[2].nome, "Voadora");

    boss->ataque[3].dano = -30;
    boss->ataque[3].nome[3] = '\0';
    strcpy(boss->ataque[3].nome, "Sermão");
}

void loadBoss3(Boss *boss){
    boss->vida = 520;
    boss->vidaMaxima = 520;
    boss->textura = LoadTexture("./assets/boss/avoDeThalya.png");

    boss->nome[0] = '\0';
    strcpy(boss->nome, "Vó de Thalya");
    
    boss->ataque[0].dano = 30;
    boss->ataque[0].nome[0] = '\0';
    strcpy(boss->ataque[0].nome, "Bengalada");

    boss->ataque[1].dano = 40; boss->ataque->chanceDeCritico = 20;
    boss->ataque[1].nome[1] = '\0';
    strcpy(boss->ataque[1].nome, "Facada");

    boss->ataque[2].dano = -20;
    boss->ataque[2].nome[2] = '\0';
    strcpy(boss->ataque[2].nome, "Artrite Fatal");

    boss->ataque[3].dano = 45;
    boss->ataque[3].nome[3] = '\0';
    strcpy(boss->ataque[3].nome, "Tricotada Mortal");
}

void loadBoss4(Boss *boss){
    boss->vida = 700;
    boss->vidaMaxima = 700;
    boss->textura = LoadTexture("./assets/boss/thalya.png");

    boss->nome[0] = '\0';
    strcpy(boss->nome, "Thalya");
    
    boss->ataque[0].dano = 25;
    boss->ataque[0].nome[0] = '\0';
    strcpy(boss->ataque[0].nome, "Malloc");

    boss->ataque[1].dano = 45; boss->ataque[1].chanceDeCritico = 33;
    boss->ataque[1].nome[1] = '\0';
    strcpy(boss->ataque[1].nome, "Batida de Cabelo");

    boss->ataque[2].dano = -80;
    boss->ataque[2].nome[2] = '\0';
    strcpy(boss->ataque[2].nome, "Come Peixe");

    boss->ataque[3].dano = 35;
    boss->ataque[3].nome[3] = '\0';
    strcpy(boss->ataque[3].nome, "Chat GPT");
}

//------------------------------

void loadAnimal1(Animal *animal){
    animal->nome[0] = '\0';
    strcpy(animal->nome, "Cagado");

    animal->intro[0] = '\0';
    strcpy(animal->intro, "Sou o Cagado que ainda\nestá vivo nessa casa");

    animal->arigato[0] = '\0';
    strcpy(animal->arigato, "Um outro foi negligênciado\ne esquecido aqui também");

    animal->itemNovo[0] = '\0';
    strcpy(animal->itemNovo, "Tudo o que sobrou foi esse casco,\nacho que ele pode te ajudar\nmais do que eu");

    animal->fim[0] = '\0';
    strcpy(animal->fim, "Agora você tem um escudo");

    animal->textura = LoadTexture("./assets/animais/cagado.png");
    animal->frame.x = 9*square; 
    animal->frame.y = 3*square;
}

void loadAnimal2(Animal *animal){
    animal->nome[0] = '\0';
    strcpy(animal->nome, "Aranha");

    animal->intro[0] = '\0';
    strcpy(animal->intro, "Sou uma das aranhas desse lugar");

    animal->arigato[0] = '\0';
    strcpy(animal->arigato, "Essa louca me confundiu com lixo,\nque absurdo!");

    animal->itemNovo[0] = '\0';
    strcpy(animal->itemNovo, "Como agradecimento, tenho esse\nbandaid de teia que fiz");
    
    animal->fim[0] = '\0';
    strcpy(animal->fim, "Agora você consegue se\ncurar durante as batalhas");


    animal->textura = LoadTexture("./assets/animais/aranha.png");
    animal->frame.x = 1*square; 
    animal->frame.y = 3*square;
}

void loadAnimal3(Animal *animal){
    animal->nome[0] = '\0';
    strcpy(animal->nome, "Galinha");

    animal->intro[0] = '\0';
    strcpy(animal->intro, "Sou uma das aves daqui");

    animal->arigato[0] = '\0';
    strcpy(animal->arigato, "As outras não tiveram tanta sorte\nquanto eu...");

    animal->itemNovo[0] = '\0';
    strcpy(animal->itemNovo, "Para te agradecer, posso me\ntransformar numa mochila com asas");
    
    animal->fim[0] = '\0';
    strcpy(animal->fim, "Agora você consegue planar e tem\nmais um ataque no arsenal");


    animal->textura = LoadTexture("./assets/animais/galinha.png");
    animal->frame.x = 7*square; 
    animal->frame.y = 8*square;
}

void loadAnimal4(Animal *animal){
    animal->nome[0] = '\0';
    strcpy(animal->nome, "Peixe");

    animal->intro[0] = '\0';
    strcpy(animal->intro, "Sou um peixe dourado");

    animal->arigato[0] = '\0';
    strcpy(animal->arigato, "Ía ser comido vivo porque\nela me confundiu com uma laranja");

    animal->itemNovo[0] = '\0';
    strcpy(animal->itemNovo, "Eu tenho um presente daqui\ndo meu aquário");
    
    animal->fim[0] = '\0';
    strcpy(animal->fim, "Obrigado por nos salvar\nagente do ibama!!!");


    animal->textura = LoadTexture("./assets/animais/peixe.png");
    animal->frame.x = 7*square; 
    animal->frame.y = 8*square;

}
//------------------------------


#endif