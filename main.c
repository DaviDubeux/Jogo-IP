#include <stdio.h>
#include <stdlib.h>
#include "C:\raylib\raylib\src\raylib.h"
#include "capivara.h"
#include "salas.h"
#include "colisao.h"

#define WIDTH 1280
#define HEIGHT 720


int main(){

    InitWindow(WIDTH, HEIGHT, "As aventuras de Thalya");
    SetTargetFPS(60);

    Capivara capivara;
    Sala sala[1];

    // LOADS
    loadCapivara(&capivara);
    loadSalas(sala);

    // LOAD TEXTURES
    capivara.spriteAtual = LoadTexture("./assets/capivara.png");


    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangleV(sala[0].frame, (Vector2){12*square, 10*square}, RED);
        DrawTextureV(capivara.spriteAtual, capivara.pos, RAYWHITE);

        EndDrawing();
    }

    UnloadTexture(capivara.spriteAtual);
    
    return 0;
}