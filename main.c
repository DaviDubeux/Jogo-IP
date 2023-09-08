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
    int menu = 1;

    const float screenWidth = (const float) GetScreenWidth();   
    const float screenHeight = (const float) GetScreenHeight();

    Capivara capivara;
    Sala sala[6];

    // LOADS
    loadCapivara(&capivara, screenWidth, screenHeight);
    for (int i = 0; i < 6; i++){ loadSalas(&(sala[i]), screenWidth, screenHeight); }
    loadSala1(&(sala[salaJardim]));
    // if (sala[salaJardim].obstaculo == NULL){
    //     for (int i = 0; i < 1; i++){ unloadSalas(&(sala[i])); printf("Erro de alocacao\n"); exit(1); }
    // }
    loadSala2(&(sala[salaHub]));
    if (sala[salaHub].obstaculo == NULL){
        for (int i = 0; i < 2; i++){ unloadSalas(&(sala[i])); printf("Erro de alocacao\n"); exit(1); }
    }
    loadSala3(&(sala[salaCagado]));
    if (sala[salaCagado].obstaculo == NULL){
        for (int i = 0; i < 3; i++){ unloadSalas(&(sala[i])); printf("Erro de alocacao\n"); exit(1); }
    }
    loadSala4(&(sala[salaAranhas]));
    // if (sala[salaAranhas].obstaculo == NULL){
    //     for (int i = 0; i < 4; i++){ unloadSalas(&(sala[i])); printf("Erro de alocacao\n"); exit(1); }
    // }
    loadSala5(&(sala[salaGalinha]));
    // if (sala[salaGalinha].obstaculo == NULL){
    //     for (int i = 0; i < 5; i++){ unloadSalas(&(sala[i])); printf("Erro de alocacao\n"); exit(1); }
    // }
    loadSala6(&(sala[salaPeixe]));
    // if (sala[salaPeixe].obstaculo == NULL){
    //     for (int i = 0; i < 6; i++){ unloadSalas(&(sala[i])); printf("Erro de alocacao\n"); exit(1); }
    // }

    // ANIMATION
        int desenho_capivara = square;
        int clique = 0;
    //
    
    while(!WindowShouldClose()){
        if (menu){
            // menu
            if (IsKeyPressed(KEY_Q)){
                menu = 0;
            }

            BeginDrawing();
            ClearBackground(RAYWHITE);
            EndDrawing();
        }
        else{
            double delta = GetTime() - time;
            time = GetTime();
            int salaAtual = capivara.salaAtual;

            if (IsKeyDown(KEY_W)) {
                capivara.hitbox.y -= capivara.speed * delta;
                updateFrame(&capivara);
                
                            //costas //mudar a forma como anda a cada clique
                if((((int)GetTime())%2)==1){ clique = 1; }
                else { clique = 3; }
                DrawTextureRec(capivara.sprite, (Rectangle) {(square*6) + (square * clique), 0, square, square}, capivara.frame, WHITE);
                desenho_capivara = (square * 7);
                capivara.direcao = sentidoCima;
            }

            if (IsKeyDown(KEY_S)) {
                capivara.hitbox.y += capivara.speed * delta;
                updateFrame(&capivara);

                //frente //mudar sprite depois //mudar a forma como anda a cada clique
                if(((int)GetTime())%2==1){ clique = 1; }
                else { clique = 3; }
                DrawTextureRec(capivara.sprite, (Rectangle) { (square * clique), 0, square, square}, capivara.frame, WHITE);
                desenho_capivara = (square * 1);
                capivara.direcao = sentidoBaixo;
            }

            if (IsKeyDown(KEY_D)) {
                capivara.hitbox.x += capivara.speed * delta;
                updateFrame(&capivara);

                //direita //mudar a forma como anda a cada clique
                if(((int)GetTime())%2==1){ clique = 1; }
                else { clique = 3; }
                DrawTextureRec(capivara.sprite, (Rectangle) { (square * clique), 0, square, square}, capivara.frame, WHITE);
                desenho_capivara = (square * 1);
                capivara.direcao = sentidoDireita;
            }

            if (IsKeyDown(KEY_A)) {
                capivara.hitbox.x -= capivara.speed * delta;
                updateFrame(&capivara);

                //esquerda //mudar a forma como anda a cada clique
                if(((int)GetTime())%2==1){ clique = 1; }
                else { clique = 3; }
                DrawTextureRec(capivara.sprite, (Rectangle) {(square*3) + (square * clique), 0, square, square}, capivara.frame, WHITE);
                desenho_capivara = (square * 4);
                capivara.direcao = sentidoEsquerda;
            }

            if (IsKeyDown(KEY_J)){ capivara.interacao.interagindo = 1; }
            else{ capivara.interacao.interagindo = 0; }


            fixCollision(&capivara, &(sala[salaAtual]));
            //updateDirection(&capivara);

            updateRoom(&capivara, &(sala[salaAtual]));
            updateInteracaoHitbox(&capivara);

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

            // desenha obstaculos
            for (int i = 0; i < sala[salaAtual].qtdObstaculos; i++){
                DrawRectangle(sala[salaAtual].obstaculo[i].x, sala[salaAtual].obstaculo[i].y,
                            sala[salaAtual].obstaculo[i].width, sala[salaAtual].obstaculo[i].height,
                            (CheckCollisionRecs(sala[salaAtual].obstaculo[i], capivara.hitbox)) ? SKYBLUE : DARKBLUE);
                if (capivara.interacao.interagindo){
                    DrawRectangle(sala[salaAtual].obstaculo[i].x, sala[salaAtual].obstaculo[i].y,
                                  sala[salaAtual].obstaculo[i].width, sala[salaAtual].obstaculo[i].height,
                                  (CheckCollisionRecs(sala[salaAtual].obstaculo[i], capivara.interacao.hitbox)) ? SKYBLUE : DARKBLUE);
                }
            }

            // desenha capivara
            DrawRectangle(capivara.hitbox.x, capivara.hitbox.y, capivara.hitbox.width, capivara.hitbox.height, GOLD);

            if (capivara.interacao.interagindo){ DrawRectangle(capivara.interacao.hitbox.x, capivara.interacao.hitbox.y,
                                                 capivara.hitbox.width, capivara.hitbox.height, PINK); }

            // DEBUG DE COLISÃO--------------------------------------------------------------


            // anima a capivara normalmente desde o último movimento
            int par = ((int)GetTime())%2;
            DrawTexture(sala[salaAtual].textura, sala[salaAtual].posImagem.x, sala[salaAtual].posImagem.y, RAYWHITE);
            DrawTextureRec(capivara.sprite, (Rectangle) {(desenho_capivara - square) + (square * par), 0, square, square}, capivara.frame, WHITE);
            capivara.prevHitbox = capivara.hitbox;

            if (IsKeyPressed(KEY_Q)){ menu = 1; }

            EndDrawing();
        }
    }

    //UNLOADS / FREES
    UnloadTexture(capivara.sprite);
    for (int i = 0; i < 6; i++){ unloadSalas(&(sala[i])); }
    
    return 0;
}