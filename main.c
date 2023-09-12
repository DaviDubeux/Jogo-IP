#include <stdio.h>
#include <stdlib.h>
#include "C:\raylib\raylib\src\raylib.h"
#include "personagens.h"
#include "salas.h"
#include "colisao.h"
#include "combate.h"

int main(){
    int gameMode = menu;
    int prevGameMode = explorando;
    int opcao = 0;
    int par = 0;
    int vez = escolherAtaqueCapivara;
    char vidaExibidaCapivara[10] = "";
    char vidaExibidaBoss[10] = "";
    char ataqueExibido[50] = "";
    int ataqueDoBoss = 0;
    char rodada[100];
    char danoDoAtaque[10];

    //menu
    Texture2D setas, TecX, TecZ;
    int opcoes = 0;
    int creditos = 0;

    InitWindow(1920, 1080, "Missão IBAMA: Contra-Ataque a Thalya");
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

    loadBoss1(&(boss[0]));
    loadBoss2(&(boss[1]));
    loadBoss3(&(boss[2]));
    loadBoss4(&(boss[3]));

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
    if (sala[salaGalinha].obstaculo == NULL){
        for (int i = 0; i < 5; i++){ unloadSalas(&(sala[i])); printf("Erro de alocacao\n"); exit(1); }
    }
    loadSala6(&(sala[salaPeixe]));
    // if (sala[salaPeixe].obstaculo == NULL){
    //     for (int i = 0; i < 6; i++){ unloadSalas(&(sala[i])); printf("Erro de alocacao\n"); exit(1); }
    // }
    
    loadArena(&arena, screenWidth, screenHeight);
    loadCapivaraCombate(&capivara, &arena);
    
    setas = LoadTexture("./assets/setas.png");
    setas.height = 350.0f;
    setas.width = 350.0f;

    TecX = LoadTexture("./assets/teclax.png");
    TecX.height = 100.0f;
    TecX.width = 100.0f;

    TecZ = LoadTexture("./assets/teclaz.png");
    TecZ.height = 100.0f;
    TecZ.width = 100.0f;
    
    // ANIMATION
        int desenho_capivara = square, 
            desenho_skin = 0; //se quiser mudar a skin soma 2*square
        int clique = 0; 
    //
    
    while(!WindowShouldClose()){
//-------------------------------------------------------------------MENU-------------------------------------------------------------------
        if (gameMode == menu){
            // menu
            BeginDrawing();
            ClearBackground(DARKBLUE);
            
            // Colocar em uma função
            //DrawText("Click Me", button_0.rect.x + button_0.rect.width / 2 - MeasureText("Click Me", 20) / 2, button_0.rect.y + button_0.rect.height / 2 - 20 / 2, 20, WHITE);

            if(opcoes == 0 && creditos == 0){ opcao = 0; }
            if(IsKeyPressed(KEY_W) && creditos == 0){ opcao = 1; }
            if(IsKeyPressed(KEY_E) && opcoes == 0){ opcao = 2; }

            //Entrar no jogo
            if(opcao == 0){
                DrawText("Missão IBAMA: Contra-Ataque a Thalya", screenHeight / 2 - MeasureText("Missão IBAMA: Contra-Ataque a Thalya", 20) / 2, 15, 60, LIME);

                DrawRectangleRec((Rectangle){75, screenHeight / 2 - 200, 500, 100}, RED);
                DrawText("Aperte Q para iniciar", 75 + 250 - MeasureText("Aperte Q para iniciar", 20) / 2, screenHeight / 2 - 200 + 50 - 20 / 2, 20, BLACK);
                
                //Controles
                DrawRectangleRec((Rectangle){75, screenHeight / 2 , 400, 100}, RED);
                DrawText("Aperte W para ver controles", 75 + 200 - MeasureText("Aperte W para ver controles", 20) / 2, screenHeight / 2 + 50 - 20 / 2, 20, BLACK);

                //Creditos
                DrawRectangleRec((Rectangle){75, screenHeight / 2 + 200, 400, 100}, RED);
                DrawText("Aperte E para ver os creditos", 75 + 200 - MeasureText("Aperte E para ver os creditos", 20) / 2, screenHeight / 2 + 200 + 50 - 20 / 2, 20, BLACK);
            }
            if(opcao == 1){
                opcoes = 1;
                ClearBackground(GRAY);
                DrawText("Use as setas do teclado para se movimentar", 75, 210, 50, WHITE);
                //Z para interagir e X para passar dos dialogos
                DrawTextureRec(setas,(Rectangle){0, 0, 350, 350}, (Vector2){ 180, 200}, GRAY);
                DrawTextureRec(TecZ,(Rectangle){0, 0, 100, 100}, (Vector2){ 180, 580}, GRAY);
                DrawTextureRec(TecX,(Rectangle){0, 0, 100, 100}, (Vector2){ 430, 580}, GRAY);

                DrawText("Z para interagir com objetos  \nX para passar dialogos", 100, 750, 36, WHITE);

                DrawText("Pressione B para retornar ao menu", 100, 950, 55, MAROON);

                if(IsKeyPressed(KEY_B)){
                    opcoes = 0;
                }
            }
            if(opcao == 2){
                creditos = 1;
                ClearBackground(SKYBLUE);
                DrawText(" Autores:\n Davi Dubeux \n Henrique Carvalho \n J.Pedro Marinho \n Mayres Mauricio Andrey \n Thalya Mayara(Detentora dos direitos da historia) \n Victor Bastos", 80, 210, 50, DARKPURPLE);
                
                DrawText("Pressione B para retornar ao menu", 100, 950, 55, MAROON);
                if(IsKeyPressed(KEY_B)){
                    creditos = 0;
                }
            }
            
            
            EndDrawing();

            if (IsKeyPressed(KEY_Q)){ gameMode = prevGameMode; }
        }
//----------------------------------------------------------------EXPLORANDO----------------------------------------------------------------
        else if (gameMode == explorando){
            double delta = GetTime() - time;
            time = GetTime();
            int salaAtual = capivara.salaAtual;


            if (IsKeyDown(KEY_UP)) {
                capivara.hitbox.y -= capivara.speed * delta;
                updateFrame(&capivara);
                
                //costas //ainda falta animar isso
                //if((((int)GetTime())%2)==1){ clique = 0; }
                //else { clique = 1; }
                DrawTextureRec(capivara.textura, (Rectangle) {(square*7), desenho_skin + (square * clique), square, square}, capivara.frame, WHITE);
                desenho_capivara = (square * 7);
                capivara.direcao = sentidoCima;
            }

            if (IsKeyDown(KEY_DOWN)) {
                capivara.hitbox.y += capivara.speed * delta;
                updateFrame(&capivara);

                //frente //ainda falta animar isso
                //if(((int)GetTime())%2==1){ clique = 0; }
                //else { clique = 1; }
                DrawTextureRec(capivara.textura, (Rectangle) { (square*10), desenho_skin + (square * clique), square, square}, capivara.frame, WHITE);
                desenho_capivara = (square * 10);
                capivara.direcao = sentidoBaixo;
            }

            if (IsKeyDown(KEY_RIGHT)) {
                capivara.hitbox.x += capivara.speed * delta;
                updateFrame(&capivara);

                //direita //ainda falta animar isso
                //if(((int)GetTime())%2==1){ clique = 0; }
                //else { clique = 1; }
                DrawTextureRec(capivara.textura, (Rectangle) { square, desenho_skin + (square * clique), square, square}, capivara.frame, WHITE);
                desenho_capivara = (square * 1);
                capivara.direcao = sentidoDireita;
            }

            if (IsKeyDown(KEY_LEFT)) {
                capivara.hitbox.x -= capivara.speed * delta;
                updateFrame(&capivara);

                //esquerda //ainda falta animar isso
                //if(((int)GetTime())%2==1){ clique = 0; }
                //else { clique = 1; }
                DrawTextureRec(capivara.textura, (Rectangle) {(square*4) , desenho_skin + (square * clique), square, square}, capivara.frame, WHITE);
                desenho_capivara = (square * 4);
                capivara.direcao = sentidoEsquerda;
            }

            if (IsKeyDown(KEY_Z)){ capivara.interacao.interagindo = 1; }
            else{ capivara.interacao.interagindo = 0; }


            fixCollision(&capivara, &(sala[salaAtual]));

            updateRoom(&capivara, &(sala[salaAtual]));
            updateInteracaoHitbox(&capivara);

            BeginDrawing();
            ClearBackground(RAYWHITE);

            // -----------------------------------------------DEBUG DE COLISÃO--------------------------------------------------------------
            /*
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
            */
            // -----------------------------------------------DEBUG DE COLISÃO--------------------------------------------------------------


            // anima a capivara normalmente desde o último movimento
            par = ((int)GetTime())%3;
            DrawTexture(sala[salaAtual].textura, sala[salaAtual].frame.x, sala[salaAtual].frame.y, RAYWHITE);
            DrawTextureRec(capivara.textura, (Rectangle) {(desenho_capivara - square) + (square * par), desenho_skin, square, square}, capivara.frame, WHITE);
            capivara.prevHitbox = capivara.hitbox;
            EndDrawing();

            gameMode = updateBossfight(&capivara, &(sala[salaAtual]));
            if (gameMode == combate){ prevGameMode = explorando; vez = escolherAtaqueCapivara; }
            if (IsKeyPressed(KEY_Q)){ gameMode = menu; prevGameMode = explorando; }
        }
//-----------------------------------------------------------------COMBATE------------------------------------------------------------------
        else if (gameMode == combate){
            int selecionado = capivara.ataqueSelecionado;
            int bossAtual = capivara.bossDerrotados;

            sprintf(vidaExibidaCapivara, "%2d/%2d", capivara.vida, capivara.vidaMaxima);
            sprintf(vidaExibidaBoss, "%2d/%2d", boss[bossAtual].vida, boss[bossAtual].vidaMaxima);

            BeginDrawing();
            ClearBackground(RAYWHITE);
            
            if (vez == escolherAtaqueCapivara){
                if (IsKeyPressed(KEY_DOWN) && selecionado < 3 &&  capivara.ataque[selecionado + 1].desbloqueado){ capivara.ataqueSelecionado++; }

                if (IsKeyPressed(KEY_UP) && selecionado > 0 &&  capivara.ataque[selecionado - 1].desbloqueado){ capivara.ataqueSelecionado--; }

                if (IsKeyPressed(KEY_Z)){
                    if (capivara.ataque[selecionado].usos > 0){
                        boss[bossAtual].vida -= capivara.ataque[selecionado].dano;
                        capivara.ataque[selecionado].usos--;
                        sprintf(rodada, "%s usou %s!\n%s levou %d de dano",
                                capivara.nome, capivara.ataque[selecionado].nome, boss[bossAtual].nome, capivara.ataque[selecionado].dano);
                        vez = mostrarAtaqueCapivara;
                    }
                    else{
                        sprintf(rodada, "você não tem mais usos para esse Ataque!");                       
                        vez = escolheuErrado;
                    }
                }
            }

            if (vez == escolherAtaqueBoss && boss[bossAtual].vida > 0){
                ataqueDoBoss = GetRandomValue(0, 3);
                capivara.vida -= boss[bossAtual].ataque[ataqueDoBoss].dano;
                sprintf(rodada, "%s usou %s!\n%s levou %d de dano",
                boss[bossAtual].nome, boss[bossAtual].ataque[ataqueDoBoss].nome, capivara.nome, boss[bossAtual].ataque[ataqueDoBoss].dano);
                vez = mostrarAtaqueBoss;
            }

            if (vez == escolherAtaqueBoss && boss[bossAtual].vida <= 0){
                sprintf(rodada, "Parabéns! Você derrotou\n%s", boss[bossAtual].nome); 
                //precisa ver quando fazer isso para depois de interagir com o animal
                desenho_skin += 2*square;
                vez = mostrarBossMorreu;
            }

            if (vez == capivaraMorreu){ sprintf(rodada, "Ah não!\nTente novamente..."); }

            // -----------------------------------------------DEBUG DE HUD------------------------------------------------------------------
            /*
            // arena retangulo cinza
            DrawRectangleV(arena.frame, (Vector2){arena.width, arena.height}, LIGHTGRAY);

            // info do personagem
            DrawRectangleV(arena.capivaraInfo.frame, (Vector2){arena.capivaraInfo.width, arena.capivaraInfo.height}, GOLD);
            DrawRectangle(arena.capivaraInfo.statsFrame.x, arena.capivaraInfo.statsFrame.y,
                          arena.capivaraInfo.statsFrame.width, arena.capivaraInfo.statsFrame.height, DARKGREEN);
            DrawText(capivara.nome, arena.capivaraInfo.nomeFrame.x, arena.capivaraInfo.nomeFrame.y, 40, BLACK);
            DrawText(vidaExibidaCapivara, arena.capivaraInfo.vidaFrame.x, arena.capivaraInfo.vidaFrame.y, 40, BLACK);
            
            // info do boss
            DrawRectangle(arena.bossInfo.frame.x, arena.bossInfo.frame.y,
                          arena.bossInfo.width, arena.bossInfo.height, GOLD);
            DrawRectangle(arena.bossInfo.statsFrame.x, arena.bossInfo.statsFrame.y,
                          arena.bossInfo.statsFrame.width, arena.bossInfo.statsFrame.height, DARKGREEN);
            DrawText(boss[bossAtual].nome, arena.bossInfo.nomeFrame.x, arena.bossInfo.nomeFrame.y, 40, BLACK);
            DrawText(vidaExibidaBoss, arena.bossInfo.vidaFrame.x, arena.bossInfo.vidaFrame.y, 40, BLACK);

            // box dos ataques
            DrawRectangle(arena.frame.x, arena.frame.y + 7*square, 8*square, 3*square, SKYBLUE);
            
            // box do dano
            DrawRectangle(arena.frame.x + 8*square, arena.frame.y + 7*square, 4*square, 3*square, BLUE);

            if (vez == escolherAtaqueCapivara){
                // ataques
                for (int i = 0; i < 4; i++){
                    DrawRectangle(capivara.ataque[i].frame.x, capivara.ataque[i].frame.y,
                                capivara.ataque[i].width, capivara.ataque[i].height,
                                (i%2 == 0) ? LIGHTGRAY : DARKGRAY);
                    
                }
                DrawCircle(capivara.ataque[selecionado].frame.x - 0.5*square, capivara.ataque[selecionado].frame.y + 0.375*square,
                           0.375*square, ORANGE);
                DrawRectangle(arena.ataqueInfo.x, arena.ataqueInfo.y, arena.ataqueInfo.width, arena.ataqueInfo.height, LIGHTGRAY);
            }
            else{
                DrawRectangle(arena.frame.x, arena.frame.y + 7*square, 12*square, 3*square, SKYBLUE);
                DrawText(rodada, arena.frame.x, arena.frame.y + 7*square, 40, BLACK);
            }

            
            */
            // -----------------------------------------------DEBUG DE HUD------------------------------------------------------------------

            if (vez == escolherAtaqueCapivara){
                DrawTexture(arena.texturaEscolherAtaque, arena.frame.x, arena.frame.y, RAYWHITE);
                for (int i = 0; i < 4; i++){
                    if (capivara.ataque[i].desbloqueado){
                        sprintf(ataqueExibido, "%s %d/%d", capivara.ataque[i].nome, capivara.ataque[i].usos, capivara.ataque[i].usosMaximo);
                    }
                    else{ sprintf(ataqueExibido, "-"); }
                    DrawText(ataqueExibido, capivara.ataque[i].frame.x, capivara.ataque[i].frame.y + 0.1875*square, 30, BLACK);
                }
                DrawTriangle((Vector2){capivara.ataque[selecionado].frame.x - 0.75*square, capivara.ataque[selecionado].frame.y + 0.1*square},
                             (Vector2){capivara.ataque[selecionado].frame.x - 0.75*square, capivara.ataque[selecionado].frame.y + 0.6*square},
                             (Vector2){capivara.ataque[selecionado].frame.x - 0.5*square, capivara.ataque[selecionado].frame.y + 0.35*square},
                             BLACK);
                // DrawCircle(capivara.ataque[selecionado].frame.x - 0.5*square, capivara.ataque[selecionado].frame.y + 0.375*square,
                //            0.15*square, DARKGRAY);
                sprintf(danoDoAtaque, "%2d de dano", capivara.ataque[selecionado].dano);
                DrawText(danoDoAtaque, arena.ataqueInfo.x + 0.5*square, arena.ataqueInfo.y + 0.5*square, 40, BLACK);
            }
            else{
                DrawTexture(arena.texturaFalas, arena.frame.x, arena.frame.y, RAYWHITE);
                DrawText(rodada, arena.frame.x, arena.frame.y + 7*square, 40, BLACK);
            }

            EndDrawing();

            if (IsKeyPressed(KEY_X) && vez == mostrarAtaqueCapivara){ vez = escolherAtaqueBoss; }
            if (IsKeyPressed(KEY_X) && vez == mostrarAtaqueBoss){ vez = escolherAtaqueCapivara; }
            if (IsKeyPressed(KEY_X) && vez == escolheuErrado){ vez = escolherAtaqueCapivara; }
            if (IsKeyPressed(KEY_X) && vez == capivaraMorreu){ gameMode = gameOver; }
            if (IsKeyPressed(KEY_X) && vez == mostrarBossMorreu){
                capivara.vida = capivara.vidaMaxima;
                capivara.bossDerrotados++;
                capivara.ataque[capivara.bossDerrotados].desbloqueado = true;
                for (int i = 0; i < 4; i++){ capivara.ataque[i].usos = capivara.ataque[i].usosMaximo; }
                gameMode = explorando;
            }

            if (IsKeyPressed(KEY_Q)){ gameMode = menu; prevGameMode = combate; }
        }
//-----------------------------------------------------------------GAMEOVER-----------------------------------------------------------------
        else if (gameMode == gameOver){
            // Reload
            loadCapivaraExplorando(&capivara, screenWidth, screenHeight);

            loadBoss1(&(boss[0]));
            loadBoss2(&(boss[1]));
            loadBoss3(&(boss[2]));
            loadBoss4(&(boss[3]));

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
            if (sala[salaGalinha].obstaculo == NULL){
                for (int i = 0; i < 5; i++){ unloadSalas(&(sala[i])); printf("Erro de alocacao\n"); exit(1); }
            }
            loadSala6(&(sala[salaPeixe]));
            // if (sala[salaPeixe].obstaculo == NULL){
            //     for (int i = 0; i < 6; i++){ unloadSalas(&(sala[i])); printf("Erro de alocacao\n"); exit(1); }
            // }

            loadArena(&arena, screenWidth, screenHeight);
            loadCapivaraCombate(&capivara, &arena);

            gameMode = menu;
            prevGameMode = explorando;
        }
    }

    //UNLOADS / FREES
    UnloadTexture(capivara.textura);
    for (int i = 0; i < 4; i++){ UnloadTexture(boss[i].textura); }
    for (int i = 0; i < 6; i++){ unloadSalas(&(sala[i])); }
    unloadArena(&arena);
    
    return 0;
}