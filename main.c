#include <stdio.h>
#include <stdlib.h>
#include "C:\raylib\raylib\src\raylib.h"
#include "capivara.h"
#include "salas.h"
#include "colisao.h"


int main(){

    InitWindow(0, 0, "As aventuras de Thalya");
    if (!IsWindowFullscreen()){ ToggleFullscreen(); }
    SetTargetFPS(60);

    const float screenWidth = (const float) GetScreenWidth();
    const float screenHeight = (const float) GetScreenHeight();
    Capivara capivara;
    Sala sala1;

    // LOADS
    loadCapivara(&capivara, screenWidth, screenHeight);
    loadSala1(&sala1, screenWidth, screenHeight);


    printf("%f, %f", capivara.pos.x, capivara.pos.y);

    // LOAD TEXTURES
    capivara.spriteAtual = LoadTexture("./assets/capivara.png");


    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangleV(sala1.pos, (Vector2){sala1.pos.x + 12*square, sala1.pos.y + 10*square}, RED);
        DrawTextureV(capivara.spriteAtual, capivara.pos, RAYWHITE);

        EndDrawing();
    }

    UnloadTexture(capivara.spriteAtual);
    
    return 0;
}