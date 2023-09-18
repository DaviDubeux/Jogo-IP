#ifndef DEFINES
#define DEFINES
#include "C:\raylib\raylib\src\raylib.h"
#define square 96.0f

//----- ----------------------------------------------------------ENUMS-------------------------------------------------------------------
enum{
    sentidoCima = 1, // sentidoCima = 1
    sentidoEsquerda, // sentidoEsquerda = 2
    sentidoDireita,  // sentidoDireita = 3
    sentidoBaixo     // sentidoBaixo = 4
}Sentido;

enum{
    escolherAtaqueCapivara,
    ataqueCriticoCapivara,
    mostrarCriticoCapivara,
    escolheuErrado,
    mostrarAtaqueCapivara,
    mostrarCuraCapivara,
    mostrarCapivaraMorreu,

    escolherAtaqueBoss,
    ataqueCriticoBoss,
    mostrarCriticoBoss,
    mostrarAtaqueBoss,
    mostrarCuraBoss,
    mostrarBossMorreu   
}Round;

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
    gameOver,    // gameOver = 3
}Mode;

enum{
    introducao,
    agradecimento,

    itemDado,
    itemMostrado,
    cenaTerminou,
} Cenas;

enum{
    cagado,
    aranha,
    galinha,
    peixe,
} Animais;

//----- ---------------------------------------------------------STRUCTS------------------------------------------------------------------
typedef struct{
    bool interagindo;
    Rectangle hitbox;
}Interacao;

typedef struct{
    int dano;
    int chanceDeCritico;
    int usos;
    int usosMaximo;
    bool desbloqueado;
    Vector2 frame;
    float width;
    float height;
    char nome[50];
}Ataque;

typedef struct{
    // gamemode explorando
    float speed;
    int direcao;
    int salaAtual;
    Vector2 frame;
    Rectangle hitbox;
    Rectangle prevHitbox;
    Interacao interacao;
    //Interacao interacao1;
    Texture2D textura;

    // gamemode combate
    char nome[50];
    int vida;
    int vidaMaxima;
    int bossDerrotados;
    int animaisResgatados;
    Ataque ataque[4];
    int ataqueSelecionado;
    Texture2D texturaCombate;
} Capivara;

//-------------------

typedef struct{
    char nome[50];
    int vida;
    int vidaMaxima;
    Ataque ataque[4];
    Texture2D textura;
}Boss;

//-------------------
typedef struct {
    char nome[50];
    Vector2 frame;
    Texture2D textura;
} Itens;

typedef struct{
    char nome[50];
    char intro[100];
    char arigato[100];
    char itemNovo[100];
    char fim[100];
    Vector2 frame;
    Itens item[50];
    Texture2D textura;
} Animal;


//-------------------

typedef struct{
    float width;
    float height;
    Vector2 frame;
    Rectangle statsFrame;
    Vector2 nomeFrame;
    Vector2 vidaFrame;
}Info;

typedef struct{
    float width;
    float height;
    Vector2 frame;
    Info capivaraInfo;
    Info bossInfo;
    Info animalInfo;
    Rectangle ataqueInfo;
    Texture2D texturaEscolherAtaque;
    Texture2D texturaDescricao;
}Arena;

//-------------------

typedef struct{
    char mensagem[500];
    Rectangle hitbox;
}Objeto;

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
    Porta porta[4];
    Saida saida[4];

    // específicos da sala
    int qtdObjetos;
    Objeto *objeto;
    Texture2D textura;
    Music musica;

}Sala;

#endif