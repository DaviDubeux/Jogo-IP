#ifndef PERSONAGENS
#define PERSONAGENS
#include "C:\raylib\raylib\src\raylib.h"
#include <string.h>
#include "defines.h"

void loadCapivaraExplorando(Capivara *capivara, const float screenW, const float screenH){
    capivara->speed = 400.0f;
    capivara->direcao = 0;
    capivara->salaAtual = 0;
    capivara->frame.x = screenW/2.0f - square/2;
    capivara->frame.y = screenH/2.0f - square/2;
    capivara->hitbox = (Rectangle) {capivara->frame.x + 4.0f, capivara->frame.y + 4.0f, square - 8.0f, square - 8.0f};
    capivara->prevHitbox = capivara->hitbox;
    capivara->interacao.hitbox = (Rectangle) {capivara->hitbox.x, capivara->hitbox.y, square - 8.0f, square - 8.0f};
    capivara->interacao.interagindo = 0;
    capivara->textura = LoadTexture("./assets/animais/capivara.png");
}

void loadCapivaraCombate(Capivara *capivara, Arena *arena){
    capivara->vida = 40;
    capivara->vidaMaxima = 40;
    capivara->bossDerrotados = 0;
    capivara->animaisResgatados =0;
    capivara->ataqueSelecionado = 0;
    capivara->texturaCombate = LoadTexture("./assets/animais/CombateCapivara.png");
    capivara->texturaCombate.width *= 3.0f; capivara->texturaCombate.height *= 3.0f;

    capivara->nome[0] = '\0';
    strcpy(capivara->nome, "Agente do ibama");

    capivara->ataque[0].dano = 10; capivara->ataque[0].chanceDeCritico = 0;
    capivara->ataque[0].usos = 20; capivara->ataque[0].usosMaximo = 4;
    capivara->ataque[0].desbloqueado = true;
    capivara->ataque[0].frame = (Vector2){arena->frame.x + 1.1*square, arena->frame.y + 7.2*square};
    capivara->ataque[0].width = 6*square; capivara->ataque[0].height = 0.75*square;
    capivara->ataque[0].nome[0] = '\0';
    strcpy(capivara->ataque[0].nome, "Canetada do Ibama");

    capivara->ataque[1].dano = 10; capivara->ataque[1].chanceDeCritico = 25;
    capivara->ataque[1].usos = 5; capivara->ataque[1].usosMaximo = 10;
    capivara->ataque[1].desbloqueado = true;
    capivara->ataque[1].frame = (Vector2){arena->frame.x + 1.1*square, arena->frame.y + 7.85*square};
    capivara->ataque[1].width = 6*square; capivara->ataque[1].height = 0.75*square;
    capivara->ataque[1].nome[0] = '\0';
    strcpy(capivara->ataque[1].nome, "Koopa troopa");

    capivara->ataque[2].dano = -5; capivara->ataque[2].chanceDeCritico = 0;
    capivara->ataque[2].usos = 10; capivara->ataque[2].usosMaximo = 10;
    capivara->ataque[2].desbloqueado = true;
    capivara->ataque[2].frame = (Vector2){arena->frame.x + 1.1*square, arena->frame.y + 8.5*square};
    capivara->ataque[2].width = 6*square; capivara->ataque[2].height = 0.75*square;
    capivara->ataque[2].nome[0] = '\0';
    strcpy(capivara->ataque[2].nome, "Bandaid de teia");

    capivara->ataque[3].dano = 30; capivara->ataque[3].chanceDeCritico = 0;
    capivara->ataque[3].usos = 10; capivara->ataque[3].usosMaximo = 10;
    capivara->ataque[3].desbloqueado = true;
    capivara->ataque[3].frame = (Vector2){arena->frame.x + 1.1*square, arena->frame.y + 9.2*square};
    capivara->ataque[3].width = 6*square; capivara->ataque[3].height = 0.75*square;
    capivara->ataque[3].nome[0] = '\0';
    strcpy(capivara->ataque[3].nome, "Pipoca com manteiga");
}

void loadBoss1(Boss *boss){
    boss->vida = 40;
    boss->vidaMaxima = 40;
    boss->textura = LoadTexture("./assets/boss/sofa.png");

    boss->nome[0] = '\0';
    strcpy(boss->nome, "Sofá de Thalya");
    
    boss->ataque[0].dano = 5;
    boss->ataque[0].nome[0] = '\0';
    strcpy(boss->ataque[0].nome, "Canhão de almofada");

    boss->ataque[1].dano = 5;
    boss->ataque[1].nome[1] = '\0';
    strcpy(boss->ataque[1].nome, "Esmagar");

    boss->ataque[2].dano = 5;
    boss->ataque[2].nome[2] = '\0';
    strcpy(boss->ataque[2].nome, "Nuvem de ácaro");

    boss->ataque[3].dano = 5;
    boss->ataque[3].nome[3] = '\0';
    strcpy(boss->ataque[3].nome, "Braçada");
    
}

void loadBoss2(Boss *boss){
    boss->vida = 20;
    boss->vidaMaxima = 20;
    boss->textura = LoadTexture("./assets/boss/tiaDeThalya.png");

    boss->nome[0] = '\0';
    strcpy(boss->nome, "Tia de Thalya");
    
    boss->ataque[0].dano = 5;
    boss->ataque[0].nome[0] = '\0';
    strcpy(boss->ataque[0].nome, "Vassourada");

    boss->ataque[1].dano = 10;
    boss->ataque[1].nome[1] = '\0';
    strcpy(boss->ataque[1].nome, "Chinelada");

    boss->ataque[2].dano = 5;
    boss->ataque[2].nome[2] = '\0';
    strcpy(boss->ataque[2].nome, "Voadora");

    boss->ataque[3].dano = 15;
    boss->ataque[3].nome[3] = '\0';
    strcpy(boss->ataque[3].nome, "Sermão");
}

void loadBoss3(Boss *boss){
    boss->vida = 20;
    boss->vidaMaxima = 20;
    boss->textura = LoadTexture("./assets/boss/avoDeThalya.png");

    boss->nome[0] = '\0';
    strcpy(boss->nome, "Vó de Thalya");
    
    boss->ataque[0].dano = 5;
    boss->ataque[0].nome[0] = '\0';
    strcpy(boss->ataque[0].nome, "Bengalada");

    boss->ataque[1].dano = 10;
    boss->ataque[1].nome[1] = '\0';
    strcpy(boss->ataque[1].nome, "Facada");

    boss->ataque[2].dano = 5;
    boss->ataque[2].nome[2] = '\0';
    strcpy(boss->ataque[2].nome, "Água Quente");

    boss->ataque[3].dano = 15;
    boss->ataque[3].nome[3] = '\0';
    strcpy(boss->ataque[3].nome, "Agulhas de tricô");
}

void loadBoss4(Boss *boss){
    boss->vida = 20;
    boss->vidaMaxima = 20;
    boss->textura = LoadTexture("./assets/boss/thalya.png");

    boss->nome[0] = '\0';
    strcpy(boss->nome, "Thalya");
    
    boss->ataque[0].dano = 5;
    boss->ataque[0].nome[0] = '\0';
    strcpy(boss->ataque[0].nome, "Raio Laser");

    boss->ataque[1].dano = 10;
    boss->ataque[1].nome[1] = '\0';
    strcpy(boss->ataque[1].nome, "Batida de Cabelo");

    boss->ataque[2].dano = 5;
    boss->ataque[2].nome[2] = '\0';
    strcpy(boss->ataque[2].nome, "Come Peixe");

    boss->ataque[3].dano = 15;
    boss->ataque[3].nome[3] = '\0';
    strcpy(boss->ataque[3].nome, "Lançar livros");
}

//------------------------------
void loadAnimal1(Animal *animal){
    animal->nome[0] = '\0';
    strcpy(animal->nome, "Cagado");

    animal->objeto[0] = '\0';
    strcpy(animal->objeto, "Escudo");

    animal->mensagem[0] = '\0';
    strcpy(animal->mensagem, "Lorem ipsum dolor sit");

    animal->textura = LoadTexture("./assets/animais/cagado.png");

}

void loadAnimal2(Animal *animal){
    animal->nome[0] = '\0';
    strcpy(animal->nome, "Aranha");

    animal->objeto[0] = '\0';
    strcpy(animal->objeto, "Bandaid");

    animal->mensagem[0] = '\0';
    strcpy(animal->mensagem, "Lorem ipsum dolor sit");

    animal->textura = LoadTexture("./assets/animais/aranha.png");

}

void loadAnimal3(Animal *animal){
    animal->nome[0] = '\0';
    strcpy(animal->nome, "Galinha");

    animal->objeto[0] = '\0';
    strcpy(animal->objeto, "Mochila com asas");

    animal->mensagem[0] = '\0';
    strcpy(animal->mensagem, "Lorem ipsum dolor sit");

    animal->textura = LoadTexture("./assets/animais/galinha.png");

}

void loadAnimal4(Animal *animal){
    animal->nome[0] = '\0';
    strcpy(animal->nome, "Peixe");

    animal->objeto[0] = '\0';
    strcpy(animal->objeto, "Coroa");

    animal->mensagem[0] = '\0';
    strcpy(animal->mensagem, "Lorem ipsum dolor sit");

    animal->textura = LoadTexture("./assets/animais/peixe.png");

}
//------------------------------

void updateHitbox(Capivara *capivara){
    capivara->hitbox.x = capivara->frame.x + 4.0f;
    capivara->hitbox.y = capivara->frame.y + 4.0f;
}

void updateFrame(Capivara *capivara){
    capivara->frame.x = capivara->hitbox.x - 4.0f;
    capivara->frame.y = capivara->hitbox.y - 4.0f;
}

void updateInteracaoHitbox(Capivara *capivara){
    
    if (capivara->direcao == sentidoCima){
        capivara->interacao.hitbox.y = capivara->hitbox.y - square - 2.0f;
        capivara->interacao.hitbox.x = capivara->hitbox.x;
    }
    else if (capivara->direcao == sentidoBaixo){
        capivara->interacao.hitbox.y = capivara->hitbox.y + square + 2.0f;
        capivara->interacao.hitbox.x = capivara->hitbox.x;
    }
    else if (capivara->direcao == sentidoEsquerda){
        capivara->interacao.hitbox.y = capivara->hitbox.y;
        capivara->interacao.hitbox.x = capivara->hitbox.x - square - 2.0f;
    }
    else if (capivara->direcao == sentidoDireita){
        capivara->interacao.hitbox.y = capivara->hitbox.y;
        capivara->interacao.hitbox.x = capivara->hitbox.x + square + 2.0f;
    }

}


#endif