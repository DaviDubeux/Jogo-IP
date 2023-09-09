#include <stdio.h>
#include <stdlib.h>
#include "C:\raylib\raylib\src\raylib.h"
#include "personagens.h"
#include "salas.h"
#include "colisao.h"
#include "combate.h"

int main(){
    int gameMode = menu;

    InitWindow(1920, 1080, "As aventuras de Thalya");
    //if (!IsWindowFullscreen()){ ToggleFullscreen(); }
    SetTargetFPS(60);

    double time = GetTime();

    const float screenWidth = (const float) GetScreenWidth();   
    const float screenHeight = (const float) GetScreenHeight();

    Capivara capivara;
    Boss boss[4];
    Sala sala[6];
    Arena arena;

//-------------------------------------------------------------------LOADS-------------------------------------------------------------------
    loadCapivaraExplorando(&capivara, screenWidth, screenHeight);

    for (int i = 0; i < 4; i++){ loadBoss(&(boss[i])); }

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
    if (sala[salaAranhas].obstaculo == NULL){
        for (int i = 0; i < 4; i++){ unloadSalas(&(sala[i])); printf("Erro de alocacao\n"); exit(1); }
    }
    loadSala5(&(sala[salaGalinha]));
    // if (sala[salaGalinha].obstaculo == NULL){
    //     for (int i = 0; i < 5; i++){ unloadSalas(&(sala[i])); printf("Erro de alocacao\n"); exit(1); }
    // }
    loadSala6(&(sala[salaPeixe]));
    // if (sala[salaPeixe].obstaculo == NULL){
    //     for (int i = 0; i < 6; i++){ unloadSalas(&(sala[i])); printf("Erro de alocacao\n"); exit(1); }
    // }

    loadArena(&arena, screenWidth, screenHeight);
    loadCapivaraCombate(&capivara, &arena);

    // ANIMATION
    int desenho_capivara = square;
    int clique = 0;
    //
    
    while(!WindowShouldClose()){
//-------------------------------------------------------------------MENU-------------------------------------------------------------------
        if (gameMode == menu){
            // menu
            BeginDrawing();
            ClearBackground(RAYWHITE);
            EndDrawing();

            if (IsKeyPressed(KEY_Q)){ gameMode = explorando; }
        }
//----------------------------------------------------------------EXPLORANDO----------------------------------------------------------------
        else if (gameMode == explorando){
            double delta = GetTime() - time;
            time = GetTime();
            int salaAtual = capivara.salaAtual;

            if (IsKeyDown(KEY_W)) {
                capivara.hitbox.y -= capivara.speed * delta;
                updateFrame(&capivara);
                
                //costas //ainda falta animar isso
                //if((((int)GetTime())%2)==1){ clique = 0; }
                //else { clique = 1; }
                DrawTextureRec(capivara.sprite, (Rectangle) {(square*7), (square * clique), square, square}, capivara.frame, WHITE);
                desenho_capivara = (square * 7);
                capivara.direcao = sentidoCima;
            }

            if (IsKeyDown(KEY_S)) {
                capivara.hitbox.y += capivara.speed * delta;
                updateFrame(&capivara);

                //frente //ainda falta animar isso
                //if(((int)GetTime())%2==1){ clique = 0; }
                //else { clique = 1; }
                DrawTextureRec(capivara.sprite, (Rectangle) { (square*10), (square * clique), square, square}, capivara.frame, WHITE);
                desenho_capivara = (square * 10);
                capivara.direcao = sentidoBaixo;
            }

            if (IsKeyDown(KEY_D)) {
                capivara.hitbox.x += capivara.speed * delta;
                updateFrame(&capivara);

                //direita //ainda falta animar isso
                //if(((int)GetTime())%2==1){ clique = 0; }
                //else { clique = 1; }
                DrawTextureRec(capivara.sprite, (Rectangle) { square, (square * clique), square, square}, capivara.frame, WHITE);
                desenho_capivara = (square * 1);
                capivara.direcao = sentidoDireita;
            }

            if (IsKeyDown(KEY_A)) {
                capivara.hitbox.x -= capivara.speed * delta;
                updateFrame(&capivara);

                //esquerda //ainda falta animar isso
                //if(((int)GetTime())%2==1){ clique = 0; }
                //else { clique = 1; }
                DrawTextureRec(capivara.sprite, (Rectangle) {(square*4) , (square * clique), square, square}, capivara.frame, WHITE);
                desenho_capivara = (square * 4);
                capivara.direcao = sentidoEsquerda;
            }

            if (IsKeyDown(KEY_J)){ capivara.interacao.interagindo = 1; }
            else{ capivara.interacao.interagindo = 0; }


            fixCollision(&capivara, &(sala[salaAtual]));

            updateRoom(&capivara, &(sala[salaAtual]));
            updateInteracaoHitbox(&capivara);

            BeginDrawing();
            ClearBackground(RAYWHITE);

            // -----------------------------------------------DEBUG DE COLISÃO--------------------------------------------------------------
            ///*
            DrawRectangleV(sala[salaAtual].frame, (Vector2){sala[salaAtual].width, sala[salaAtual].height}, LIGHTGRAY);

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

            // desenha interacao
            if (capivara.interacao.interagindo){ DrawRectangle(capivara.interacao.hitbox.x, capivara.interacao.hitbox.y,
                                                 capivara.hitbox.width, capivara.hitbox.height, PINK); }
            //*/
            // -----------------------------------------------DEBUG DE COLISÃO--------------------------------------------------------------


            // anima a capivara normalmente desde o último movimento
            int par = ((int)GetTime())%3;
            // DrawTexture(sala[salaAtual].textura, sala[salaAtual].frame.x, sala[salaAtual].frame.y, RAYWHITE);
            DrawTextureRec(capivara.sprite, (Rectangle) {(desenho_capivara - square) + (square * par), 0, square, square}, capivara.frame, WHITE);
            capivara.prevHitbox = capivara.hitbox;
            EndDrawing();

            gameMode = updateBossfight(&capivara, &(sala[salaAtual]));
            if (IsKeyPressed(KEY_Q)){ gameMode = menu; }
        }
//-----------------------------------------------------------------COMBATE------------------------------------------------------------------
        else if (gameMode == combate){
            int salaAtual = capivara.salaAtual;

            BeginDrawing();
            ClearBackground(BLUE);

            // -----------------------------------------------DEBUG DE HUD------------------------------------------------------------------
            DrawRectangleV(arena.frame, (Vector2){arena.width, arena.height}, LIGHTGRAY);

            DrawRectangleV(arena.capivaraInfo.frame, (Vector2){arena.capivaraInfo.width, arena.capivaraInfo.height}, GOLD);
            DrawRectangle(arena.capivaraInfo.statsFrame.x, arena.capivaraInfo.statsFrame.y,
                          arena.capivaraInfo.statsFrame.width, arena.capivaraInfo.statsFrame.height, DARKGREEN);
            DrawText(capivara.nome, arena.capivaraInfo.nomeFrame.x, arena.capivaraInfo.nomeFrame.y, 20, BLACK);
            DrawText("20/20", arena.capivaraInfo.vidaFrame.x, arena.capivaraInfo.vidaFrame.y, 20, BLACK);
            
            DrawRectangle(arena.bossInfo.frame.x, arena.bossInfo.frame.y,
                          arena.bossInfo.width, arena.bossInfo.height, GOLD);
            DrawRectangle(arena.bossInfo.statsFrame.x, arena.bossInfo.statsFrame.y,
                          arena.bossInfo.statsFrame.width, arena.bossInfo.statsFrame.height, DARKGREEN);
            DrawText(boss[capivara.bossDerrotados].nome, arena.bossInfo.nomeFrame.x, arena.bossInfo.nomeFrame.y, 20, BLACK);
            DrawText("20/20", arena.bossInfo.vidaFrame.x, arena.bossInfo.vidaFrame.y, 20, BLACK);

            DrawRectangle(arena.frame.x, arena.frame.y + 7*square, 12*square, 3*square, SKYBLUE);

            for (int i = 0; i < 4; i++){
                if (capivara.ataque[0].desbloqueado){
                    DrawRectangle(capivara.ataque[i].frame.x, capivara.ataque[i].frame.y,
                                  capivara.ataque[i].width, capivara.ataque[i].height, LIGHTGRAY);
                }
                if (capivara.ataque[i].selecionado){
                    DrawCircle(capivara.ataque[i].frame.x - 0.5*square, capivara.ataque[i].frame.y + 0.25*square, 0.3*square, ORANGE);
                }
            }

            

            EndDrawing();

            if (IsKeyPressed(KEY_Q)){
                gameMode = menu;
                capivara.bossDerrotados++;
            }
        }
//---------------------------------------------------------------- GAMEOVER-----------------------------------------------------------------
        else if (gameMode == gameOver){

        }
    }

    //UNLOADS / FREES
    UnloadTexture(capivara.sprite);
    for (int i = 0; i < 6; i++){ unloadSalas(&(sala[i])); }
    
    return 0;
}