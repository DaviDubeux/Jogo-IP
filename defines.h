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
    Texture2D textura;

    // gamemode combate
    char nome[50];
    int vida;
    int vidaMaxima;
    int bossDerrotados;
    Ataque ataque[4];
    int ataqueSelecionado;
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
    Rectangle ataqueInfo;
    Texture2D texturaEscolherAtaque;
    Texture2D texturaDescricao;
}Arena;

//-------------------

typedef struct{
    char mensagem[500];
    Texture2D textura;
    Rectangle hitbox;
}Placa;

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
    int qtdObstaculos;
    Rectangle *obstaculo;
    Placa placa;
    Texture2D textura;
    Sound musica

}Sala;

#endif