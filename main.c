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
    Sala sala[6];

    // LOADS
    loadCapivara(&capivara, screenWidth, screenHeight);
    for (int i = 0; i < 6; i++){ loadSalas(&(sala[i]), screenWidth, screenHeight); }
    loadSala1(&(sala[salaJardim]), screenWidth, screenHeight);
    loadSala2(&(sala[salaHub]), screenWidth, screenHeight);
    loadSala3(&(sala[salaCagado]), screenWidth, screenHeight);
    loadSala4(&(sala[salaAranhas]), screenWidth, screenHeight);
    loadSala5(&(sala[salaGalinha]), screenWidth, screenHeight);
    loadSala6(&(sala[salaPeixe]), screenWidth, screenHeight);

    sala[salaJardim].textura.width = 1152.0f;
    sala[salaJardim].textura.height = 960.0f;
    sala[salaHub].textura.width = 1152.0f;
    sala[salaHub].textura.height = 960.0f;
    sala[salaCagado].textura.width = 1152.0f;
    sala[salaCagado].textura.height = 960.0f;
    sala[salaAranhas].textura.width = 1152.0f;
    sala[salaAranhas].textura.height = 960.0f;
    sala[salaGalinha].textura.width = 1152.0f;
    sala[salaGalinha].textura.height = 960.0f;
    sala[salaPeixe].textura.width = 1152.0f;
    sala[salaPeixe].textura.height = 960.0f;

    // ANIMATION
        int desenho_capivara = square;
        int clique_w = 0, clique_s = 0, clique_a = 0, clique_d = 0;
    //
    
    while(!WindowShouldClose()){
        double delta = GetTime() - time;
        time = GetTime();
        int salaAtual = capivara.salaAtual;


        
        
        if (IsKeyDown(KEY_W)) {
            capivara.pos.y -= capivara.speed * delta;
            capivara.hitbox.y = capivara.pos.y;
            
            //costas //mudar a forma como anda a cada clique
            clique_w++; 
            DrawTextureRec(capivara.sprite, (Rectangle) {(square*6) + (square * clique_w), 0, square, square}, capivara.pos, WHITE);
            clique_w = clique_w%2;
            desenho_capivara = (square * 7);

        }

        if (IsKeyDown(KEY_S)) {
            capivara.pos.y += capivara.speed * delta;
            capivara.hitbox.y = capivara.pos.y;

            //frente //mudar sprite depois //mudar a forma como anda a cada clique
            clique_s += 2; 
            DrawTextureRec(capivara.sprite, (Rectangle) { (square * clique_s), 0, square, square}, capivara.pos, WHITE); 
            clique_s = clique_s%2;
            desenho_capivara = (square * 1);

        }

        if (IsKeyDown(KEY_D)) {
            capivara.pos.x += capivara.speed * delta;
            capivara.hitbox.x = capivara.pos.x;

            //direita //mudar a forma como anda a cada clique
            clique_d++;
            DrawTextureRec(capivara.sprite, (Rectangle) { (square * clique_d), 0, square, square}, capivara.pos, WHITE);
            clique_d = clique_d%2;
            desenho_capivara = (square * 1);

        }

        if (IsKeyDown(KEY_A)) {
            capivara.pos.x -= capivara.speed * delta;
            capivara.hitbox.x = capivara.pos.x;

            //esquerda //mudar a forma como anda a cada clique
            clique_a++;
            DrawTextureRec(capivara.sprite, (Rectangle) {(square*3) + (square * clique_a), 0, square, square}, capivara.pos, WHITE);
            clique_a = clique_a%2;
            desenho_capivara = (square * 4);

        }

        fixCollision(&capivara, &(sala[salaAtual]));
        updateRoom(&capivara, &(sala[salaAtual]));

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // DEBUG DE COLISÃO--------------------------------------------------------------

        DrawRectangleV(sala[salaAtual].posImagem, (Vector2){sala[salaAtual].width*square, sala[salaAtual].height*square}, LIGHTGRAY);

        // desenha as paredes
        for (int i = 0; i < 8; i++){
            DrawRectangle(sala[salaAtual].paredes[i].x,     sala[salaAtual].paredes[i].y,
                          sala[salaAtual].paredes[i].width, sala[salaAtual].paredes[i].height,
                          (CheckCollisionRecs(sala[salaAtual].paredes[i], capivara.hitbox)) ? ORANGE : RED);
        }

        // desenha portas
        for (int i = 0; i < 4; i++){
            DrawRectangle(sala[salaAtual].porta[i].hitbox.x, sala[salaAtual].porta[i].hitbox.y,
                          sala[salaAtual].porta[i].hitbox.width, sala[salaAtual].porta[i].hitbox.height,
                          (sala[salaAtual].porta[i].aberta) ? BLUE : 
                          CheckCollisionRecs(sala[salaAtual].porta[i].hitbox, capivara.hitbox) ? ORANGE : RED);
        }

        // desenha saidas
        for (int i = 0; i < 4; i++){
            DrawRectangle(sala[salaAtual].saida[i].hitbox.x, sala[salaAtual].saida[i].hitbox.y,
                          sala[salaAtual].saida[i].hitbox.width, sala[salaAtual].saida[i].hitbox.height,
                          (CheckCollisionRecs(sala[salaAtual].saida[i].hitbox, capivara.hitbox)) ? GREEN : LIME);
        }

        // DEBUG DE COLISÃO--------------------------------------------------------------


        // anima a capivara normalmente desde o último movimento
        int par = ((int)GetTime())%2;
        DrawTexture(sala[salaAtual].textura, sala[salaAtual].posImagem.x, sala[salaAtual].posImagem.y, RAYWHITE);
        DrawTextureRec(capivara.sprite, (Rectangle) {(desenho_capivara - square) + (square * par), 0, square, square}, capivara.pos, WHITE);
        capivara.prevPos = capivara.pos;

        EndDrawing();
    }

    UnloadTexture(capivara.sprite);
    UnloadTexture(sala[salaJardim].textura);
    UnloadTexture(sala[salaHub].textura);
    UnloadTexture(sala[salaCagado].textura);
    UnloadTexture(sala[salaAranhas].textura);
    UnloadTexture(sala[salaGalinha].textura);
    UnloadTexture(sala[salaPeixe].textura);
    
    return 0;
}