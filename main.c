#include <stdio.h>
#include <stdlib.h>
#include "C:\raylib\raylib\src\raylib.h"
#include "capivara.h"
#include "salas.h"
#include "colisao.h"


int main(){

    InitWindow(0, 0, "As aventuras de Thalya");
    //if (!IsWindowFullscreen()){ ToggleFullscreen(); }
    SetTargetFPS(60);

    double time = GetTime();

    const float screenWidth = (const float) GetScreenWidth();   
    const float screenHeight = (const float) GetScreenHeight();

    Capivara capivara;
    Sala sala[6];

    // LOADS
    loadCapivara(&capivara, screenWidth, screenHeight);
    for (int i = 0; i < 6; i++){ loadSalas(&(sala[i]), screenWidth, screenHeight); }
    loadSala1(&(sala[0]), screenWidth, screenHeight);
    loadSala2(&(sala[1]), screenWidth, screenHeight);
    loadSala3(&(sala[2]), screenWidth, screenHeight);
    loadSala4(&(sala[3]), screenWidth, screenHeight);
    loadSala5(&(sala[4]), screenWidth, screenHeight);
    loadSala6(&(sala[5]), screenWidth, screenHeight);


    // ANIMATION
        int desenho_capivara = 96;
        int clique_w = 0, clique_s = 0, clique_a = 0, clique_d = 0;
    //
    
    while(!WindowShouldClose()){
        double delta = GetTime() - time;
        time = GetTime();
        capivara.salaAtual = 1;
        int salaAtual = capivara.salaAtual;


        
        
        if (IsKeyDown(KEY_W)) {
            capivara.pos.y -= capivara.speed * delta;
            capivara.hitbox.y = capivara.pos.y;
            
            //costas //mudar a forma como anda a cada clique
            clique_w++; 
            DrawTextureRec(capivara.sprite, (Rectangle) {(96*6) + (96 * clique_w), 0, 96, 96}, capivara.pos, WHITE);
            clique_w = clique_w%2;
            desenho_capivara = (96 * 7);

        }

        if (IsKeyDown(KEY_S)) {
            capivara.pos.y += capivara.speed * delta;
            capivara.hitbox.y = capivara.pos.y;

            //frente //mudar sprite depois //mudar a forma como anda a cada clique
            clique_s += 2; 
            DrawTextureRec(capivara.sprite, (Rectangle) { (96 * clique_s), 0, 96, 96}, capivara.pos, WHITE); 
            clique_s = clique_s%2;
            desenho_capivara = (96 * 1);

        }

        if (IsKeyDown(KEY_D)) {
            capivara.pos.x += capivara.speed * delta;
            capivara.hitbox.x = capivara.pos.x;

            //direita //mudar a forma como anda a cada clique
            clique_d++;
            DrawTextureRec(capivara.sprite, (Rectangle) { (96 * clique_d), 0, 96, 96}, capivara.pos, WHITE);
            clique_d = clique_d%2;
            desenho_capivara = (96 * 1);

        }

        if (IsKeyDown(KEY_A)) {
            capivara.pos.x -= capivara.speed * delta;
            capivara.hitbox.x = capivara.pos.x;

            //esquerda //mudar a forma como anda a cada clique
            clique_a++;
            DrawTextureRec(capivara.sprite, (Rectangle) {(96*3) + (96 * clique_a), 0, 96, 96}, capivara.pos, WHITE);
            clique_a = clique_a%2;
            desenho_capivara = (96 * 4);

        }

        fixCollision(&capivara, &sala[salaAtual]);

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
            DrawRectangle(sala[salaAtual].portas[i].hitbox.x, sala[salaAtual].portas[i].hitbox.y,
                          sala[salaAtual].portas[i].hitbox.width, sala[salaAtual].portas[i].hitbox.height,
                          (sala[salaAtual].portas[i].aberta) ? BLUE : 
                          CheckCollisionRecs(sala[salaAtual].portas[i].hitbox, capivara.hitbox) ? ORANGE : RED);
        }

        // desenha saidas
        for (int i = 0; i < 4; i++){
            DrawRectangle(sala[salaAtual].saidas[i].x, sala[salaAtual].saidas[i].y,
                          sala[salaAtual].saidas[i].width, sala[salaAtual].saidas[i].height,
                          (CheckCollisionRecs(sala[salaAtual].saidas[i], capivara.hitbox)) ? GREEN : LIME);
        }

        // DEBUG DE COLISÃO--------------------------------------------------------------


        // anima a capivara normalmente desde o último movimento
        int par = ((int)GetTime())%2;
        DrawTextureRec(capivara.sprite, (Rectangle) {(desenho_capivara - 96) + (96 * par), 0, 96, 96}, capivara.pos, WHITE);
        capivara.prevPos = capivara.pos;

        EndDrawing();
    }

    UnloadTexture(capivara.sprite);
    
    return 0;
}