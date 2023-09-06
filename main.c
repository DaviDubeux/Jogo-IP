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

    double time = GetTime();

    const float screenWidth = (const float) GetScreenWidth();   
    const float screenHeight = (const float) GetScreenHeight();
    Capivara capivara;
    Sala sala1;

    // LOADS
    loadCapivara(&capivara, screenWidth, screenHeight);
    loadSalas(&sala1, screenWidth, screenHeight);
    loadSala1(&sala1, screenWidth, screenHeight);

    printf("%f, %f", capivara.pos.x, capivara.pos.y);


    while(!WindowShouldClose()){
        double delta = GetTime() - time;
        time = GetTime();

        if (IsKeyDown(KEY_W)) {
            capivara.pos.y -= capivara.speed * delta;
            capivara.hitbox.y -= capivara.speed *delta;
        }

        if (IsKeyDown(KEY_S)) {
            capivara.pos.y += capivara.speed * delta;
            capivara.hitbox.y += capivara.speed *delta;
        }

        if (IsKeyDown(KEY_D)) {
            capivara.pos.x += capivara.speed * delta;
            capivara.hitbox.x += capivara.speed *delta;
        }

        if (IsKeyDown(KEY_A)) {
            capivara.pos.x -= capivara.speed * delta;
            capivara.hitbox.x -= capivara.speed *delta;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangleV(sala1.posImagem, (Vector2){12.0f*square, 10.0f*square}, LIGHTGRAY);

        DrawRectangle(sala1.paredes[0].x, sala1.paredes[0].y, sala1.paredes[0].width, sala1.paredes[0].height,
                    (CheckCollisionRecs(sala1.paredes[0], capivara.hitbox)) ? GREEN : RED);
        DrawRectangle(sala1.paredes[1].x, sala1.paredes[1].y, sala1.paredes[1].width, sala1.paredes[1].height,
                    (CheckCollisionRecs(sala1.paredes[1], capivara.hitbox)) ? GREEN : RED);
        DrawRectangle(sala1.paredes[2].x, sala1.paredes[2].y, sala1.paredes[2].width, sala1.paredes[2].height,
                    (CheckCollisionRecs(sala1.paredes[2], capivara.hitbox)) ? GREEN : RED);
        DrawRectangle(sala1.paredes[3].x, sala1.paredes[3].y, sala1.paredes[3].width, sala1.paredes[3].height,
                    (CheckCollisionRecs(sala1.paredes[3], capivara.hitbox)) ? GREEN : RED);
        DrawRectangle(sala1.paredes[4].x, sala1.paredes[4].y, sala1.paredes[4].width, sala1.paredes[4].height,
                    (CheckCollisionRecs(sala1.paredes[4], capivara.hitbox)) ? GREEN : RED);
        DrawRectangle(sala1.paredes[5].x, sala1.paredes[5].y, sala1.paredes[5].width, sala1.paredes[5].height,
                    (CheckCollisionRecs(sala1.paredes[5], capivara.hitbox)) ? GREEN : RED);
        DrawRectangle(sala1.paredes[6].x, sala1.paredes[6].y, sala1.paredes[6].width, sala1.paredes[6].height,
                    (CheckCollisionRecs(sala1.paredes[6], capivara.hitbox)) ? GREEN : RED);
        DrawRectangle(sala1.paredes[7].x, sala1.paredes[7].y, sala1.paredes[7].width, sala1.paredes[7].height,
                    (CheckCollisionRecs(sala1.paredes[7], capivara.hitbox)) ? GREEN : RED);

        DrawTextureV(capivara.spriteAtual, capivara.pos, RAYWHITE);

        EndDrawing();
    }

    UnloadTexture(capivara.spriteAtual);
    
    return 0;
}