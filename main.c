#include <stdio.h>
#include <stdlib.h>
#include "C:\raylib\raylib\src\raylib.h"
#include "capivara.h"


int main(){

    Capivara capivara;
    loadCapivara(&capivara);

    SetConfigFlags(FLAG_VSYNC_HINT); 
    InitWindow(0, 0, "TNG - current");
    if (!IsWindowFullscreen()) ToggleFullscreen();
    
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    
    const float W2 = screenWidth / 2.0f;
    const float H2 = screenHeight / 2.0f;
    
    InitAudioDevice();
    SetMasterVolume(0.2f);
    int playing = 0;
    
    printf("%f, %f\n", W2, H2);

    capivara.pos.x = -16.0f;
    capivara.pos.y = -16.0f;

    const float pspeed = 200.0f;
    Camera2D camera = {.offset = {screenWidth / 2.0f, screenHeight / 2.0f}, .target = {0}, .rotation = 0, .zoom = 0.5};
    
    SetTargetFPS(60);

    double time = GetTime();

    char buf[500] = {0};

    while (!WindowShouldClose() && !IsKeyPressed(KEY_CAPS_LOCK)) {
        double delta = GetTime() - time;
        time = GetTime();

        if (IsKeyDown(KEY_W)) { capivara.pos.y -= pspeed * delta; }
        if (IsKeyDown(KEY_S)) { capivara.pos.y += pspeed * delta; }
        if (IsKeyDown(KEY_D)) { capivara.pos.x += pspeed * delta; }
        if (IsKeyDown(KEY_A)) { capivara.pos.x -= pspeed * delta; }
        if (capivara.pos.x > 100.0f){ mudaPos(&capivara); }

        //camera.target.x = capivara.pos.x + .0f;
        //camera.target.y = capivara.pos.y + 10.0f;

        BeginDrawing();
        ClearBackground(BLACK);

        sprintf(buf, "%02.02f, cam: (%02.02f, %02.0f2), p (%02.02f, %02.02f)", 0.0f, camera.target.x, camera.target.y, capivara.pos.x, capivara.pos.y);
        DrawText(buf, 10, 10, 20, WHITE);

        BeginMode2D(camera);
        DrawCircle(0, 0, 10, BLUE);

        DrawTexture(capivara.spriteAtual, capivara.pos.x, capivara.pos.y, WHITE);

        if(!playing && capivara.pos.x > 1800) {
            playing = 1;
        }

 
       EndMode2D();
        EndDrawing();
    }

    UnloadTexture(capivara.spriteAtual);

    CloseAudioDevice();
    CloseWindow();
    
    return 0;
}