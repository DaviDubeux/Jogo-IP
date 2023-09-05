#include <stdio.h>
#include <stdlib.h>
#include "C:\raylib\raylib\src\raylib.h"
#include "capivara.h"

#define WIDTH 1280
#define HEIGHT 720


int main(){

    InitWindow(WIDTH, HEIGHT, "As aventuras de Thalya");
    SetTargetFPS(60);

    Capivara capivara;
    
    capivara.spriteAtual = LoadTexture("./assets/capivara.png");

    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTextureV(capivara.spriteAtual, capivara.pos, RAYWHITE);

        EndDrawing();
    }

    UnloadTexture(capivara.spriteAtual);
    
    return 0;
}