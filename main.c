#include <stdio.h>
#include <stdlib.h>
#include "C:\raylib\raylib\src\raylib.h"
#include "defines.h"
#include "personagens.h"
#include "salas.h"
#include "explorando.h"
#include "combate.h"

int main(){
    int gameMode = menu;
    int prevGameMode = explorando;
    
    //explorando
    int par = 0;
    bool pausado = false;
    bool lendoPlaca = false;
    bool lendo = false;
    int interagindoCom;
    Texture2D chaves;

    //combate
    int round = escolherAtaqueCapivara;
    int ataqueCritico = 0;
    char vidaExibidaCapivara[10] = "";
    char vidaExibidaBoss[10] = "";
    char ataqueExibido[50] = "";
    int ataqueDoBoss = 0;
    char scene[100] = "";
    char danoDoAtaque[10] = "";
    char usosDoAtaque[10] = "";
    char chanceDeCritico[10] = "";

    //menu
    Texture2D Controles, Creditos, Menu, Fundo;
    int opcao = 0;
    int opcoes = 0;
    int creditos = 0;

    //cena
    int cena = introducao;
    float Timer = 0.0f;

    Music musica;
    Music musicaCombate;

    InitWindow(1920, 1080, "Missão IBAMA: Contra-Ataque a Thalya");
    InitAudioDevice();
    SetMasterVolume(5.0);
    //if (!IsWindowFullscreen()){ ToggleFullscreen(); }
    SetTargetFPS(60);

    double time = GetTime();

    const float screenWidth = (const float) GetScreenWidth();   
    const float screenHeight = (const float) GetScreenHeight();

    Capivara capivara;
    Boss boss[4];
    Itens item;
    Animal animal[4];
    Sala sala[6];
    Arena arena;

//-------------------------------------------------------------------LOADS-------------------------------------------------------------------
    loadCapivaraExplorando(&capivara, screenWidth, screenHeight);

    loadBoss1(&(boss[0])); boss[0].textura.width *= 9.0f; boss[0].textura.height *= 9.0f;
    loadBoss2(&(boss[1])); boss[1].textura.width *= 9.0f; boss[1].textura.height *= 9.0f;
    loadBoss3(&(boss[2])); boss[2].textura.width *= 9.0f; boss[2].textura.height *= 9.0f;
    loadBoss4(&(boss[3])); boss[3].textura.width *= 9.0f; boss[3].textura.height *= 9.0f;

    loadItem(&item); item.textura.width *= 3.0f; item.textura.height *= 3.0f;

    loadAnimal1(&(animal[0])); animal[0].textura.width *= 3.0f; animal[0].textura.height *= 3.0f;
    loadAnimal2(&(animal[1])); animal[1].textura.width *= 3.0f; animal[1].textura.height *= 3.0f;
    loadAnimal3(&(animal[2])); animal[2].textura.width *= 3.0f; animal[2].textura.height *= 3.0f;
    loadAnimal4(&(animal[3])); animal[3].textura.width *= 3.0f; animal[3].textura.height *= 3.0f;

    for (int i = 0; i < 6; i++){ loadSalas(&(sala[i]), screenWidth, screenHeight); }
    loadSala1(&(sala[salaJardim]));
    if (sala[salaJardim].objeto == NULL){
        for (int i = 0; i < 1; i++){ unloadSalas(&(sala[i])); printf("Erro de alocacao\n"); exit(1); }
    }
    loadSala2(&(sala[salaHub]));
    if (sala[salaHub].objeto == NULL){
        for (int i = 0; i < 2; i++){ unloadSalas(&(sala[i])); printf("Erro de alocacao\n"); exit(1); }
    }
    loadSala3(&(sala[salaCagado]));
    if (sala[salaCagado].objeto == NULL){
        for (int i = 0; i < 3; i++){ unloadSalas(&(sala[i])); printf("Erro de alocacao\n"); exit(1); }
    }
    loadSala4(&(sala[salaAranhas]));
    if (sala[salaAranhas].objeto == NULL){
        for (int i = 0; i < 4; i++){ unloadSalas(&(sala[i])); printf("Erro de alocacao\n"); exit(1); }
    }
    loadSala5(&(sala[salaGalinha]));
    if (sala[salaGalinha].objeto == NULL){
        for (int i = 0; i < 5; i++){ unloadSalas(&(sala[i])); printf("Erro de alocacao\n"); exit(1); }
    }
    loadSala6(&(sala[salaPeixe]));
    if (sala[salaPeixe].objeto == NULL){
        for (int i = 0; i < 6; i++){ unloadSalas(&(sala[i])); printf("Erro de alocacao\n"); exit(1); }
    }
    
    loadArena(&arena, screenWidth, screenHeight);
    loadCapivaraCombate(&capivara, &arena);
    
    Controles = LoadTexture("./assets/cenarios/menu/tutorial.png");
    Controles.height = screenHeight;
    Controles.width = screenWidth;

    Menu = LoadTexture("./assets/cenarios/menu/Menu.png");
    Menu.height = screenHeight;
    Menu.width = screenWidth;

    Creditos = LoadTexture("./assets/cenarios/menu/creditos.png");
    Creditos.height = screenHeight;
    Creditos.width = screenWidth;

    Fundo = LoadTexture("./assets/cenarios/menu/ibamaFundo.png");
    Fundo.height = screenHeight;
    Fundo.width = screenWidth;

    chaves = LoadTexture("./assets/cenarios/explorando/chaves_64.png");
    chaves.width = 64.0f; chaves.height = 256.0f;

    Texture2D texturaPlaca = LoadTexture("./assets/cenarios/explorando/lendoPlaca.png");
    texturaPlaca.width = 8*square; texturaPlaca.height = 6*square;
    Texture2D texturaLendo = LoadTexture("./assets/cenarios/explorando/lendo.png");
    texturaLendo.width *= 3; texturaLendo.height *= 3;

    musica = LoadMusicStream("./assets/musicas/musica.mp3");
    musicaCombate = LoadMusicStream("./assets/musicas/musicaCombate.mp3");
    
    // ANIMATION
        int desenho_capivara = square, 
            desenho_skin = 0, //se quiser mudar a skin soma 2*square
            desenho_skin_combate = 0; //se quiser mudar a skin soma 3||4*square
    //
    
    while(!WindowShouldClose()){
//-------------------------------------------------------------------MENU-------------------------------------------------------------------
        if (gameMode == menu){
            UpdateMusicStream(musica);
            PlayMusicStream(musica);
            SetMusicVolume(musica, 1.2);
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
                DrawTextureRec(Menu,(Rectangle){0, 0, screenWidth, screenHeight}, (Vector2){0, 0}, RAYWHITE);
                
            }
            if(opcao == 1){
                opcoes = 1;
                DrawTextureRec(Controles,(Rectangle){0, 0, screenWidth, screenHeight}, (Vector2){ 0, 0}, RAYWHITE);

                if(IsKeyPressed(KEY_B)){ opcoes = 0; }
            }
            if(opcao == 2){
                creditos = 1;
                DrawTextureRec(Creditos,(Rectangle){0, 0, screenWidth, screenHeight}, (Vector2){ 0, 0}, RAYWHITE);
                if(IsKeyPressed(KEY_B)){ creditos = 0; }
            }

            EndDrawing();

            if (IsKeyPressed(KEY_Q)){ gameMode = prevGameMode; }
        }
//----------------------------------------------------------------EXPLORANDO----------------------------------------------------------------
        else if (gameMode == explorando){
            double delta = GetTime() - time;
            time = GetTime();
            int salaAtual = capivara.salaAtual;
            int numeroDaChave = capivara.chaves - 1;

            if (capivara.salaAtual == salaJardim){ UpdateMusicStream(sala[salaJardim].musica); }
            else{ UpdateMusicStream(sala[salaHub].musica); }
            PlayMusicStream(sala[salaAtual].musica);
            SetMusicVolume(sala[salaAtual].musica, 1.0f);

            if(!pausado){
                if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))) {
                    capivara.hitbox.y -= capivara.speed * delta;
                    updateFrame(&capivara);
                    DrawTextureRec(capivara.textura, (Rectangle) {(square*7), desenho_skin, square, square}, capivara.frame, WHITE);
                    desenho_capivara = (square * 7);
                    capivara.direcao = sentidoCima;
                }

                if ((IsKeyDown(KEY_DOWN)  || IsKeyDown(KEY_S))) {
                    capivara.hitbox.y += capivara.speed * delta;
                    updateFrame(&capivara);
                    DrawTextureRec(capivara.textura, (Rectangle) { (square*10), desenho_skin, square, square}, capivara.frame, WHITE);
                    desenho_capivara = (square * 10);
                    capivara.direcao = sentidoBaixo;
                }

                if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))) {
                    capivara.hitbox.x += capivara.speed * delta;
                    updateFrame(&capivara);
                    DrawTextureRec(capivara.textura, (Rectangle) { square, desenho_skin, square, square}, capivara.frame, WHITE);
                    desenho_capivara = (square * 1);
                    capivara.direcao = sentidoDireita;
                }

                if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))) {
                capivara.hitbox.x -= capivara.speed * delta;
                updateFrame(&capivara);
                DrawTextureRec(capivara.textura, (Rectangle) {(square*4) , desenho_skin, square, square}, capivara.frame, WHITE);
                desenho_capivara = (square * 4);
                capivara.direcao = sentidoEsquerda;
            }
            }
            //tem algo de errado
            else if(!lendo){
                //desenho da cena com os animais
                if(capivara.bossDerrotados == 0){
                    DrawTexture(sala[salaCagado].textura, sala[salaCagado].frame.x, sala[salaCagado].frame.y, DARKGRAY);
                    DrawTextureRec(capivara.textura, (Rectangle) { square*(((int)(Timer))%2), desenho_skin, square, square}, (Vector2){ capivara.frame.x, capivara.frame.y}, RAYWHITE);
                    DrawTextureRec(animal[cagado].textura, (Rectangle) { square*(((int)(Timer))%2), square/3, square, square}, animal->frame, RAYWHITE);
                    DrawRectangle(5*square, 7*square, 2*square, square, WHITE);

                    if(cena == introducao){
                        DrawText(animal[cagado].intro, 5.5*square, 7.5*square, 25, BLACK);
                    }
                    if(cena == agradecimento){
                        DrawText(animal[cagado].arigato, 5.5*square, 7.5*square, 25, BLACK);
                    }
                    if(cena == itemDado){
                        DrawText(animal[cagado].itemNovo, 5.5*square, 7.5*square, 25, BLACK);
                    }
                    if(cena == itemMostrado){
                        DrawTexture(sala[salaCagado].textura, sala->frame.x, sala[salaCagado].frame.y, DARKGRAY);
                        DrawTextureRec(capivara.textura, (Rectangle) { 0, desenho_skin, square, square}, (Vector2){ capivara.frame.x, capivara.frame.y}, GRAY);
                        DrawTextureRec(animal[cagado].textura, (Rectangle) { 0, square/3, square, square}, animal[cagado].frame, GRAY);
                        DrawTextureRec(item.textura, (Rectangle) { 0, 0, square, square}, item.frame, RAYWHITE);
                        DrawRectangle(5*square, 7*square, 2*square, square, WHITE);
                        DrawText(animal[cagado].item->nome, 5.5*square, 7.5*square, 25, BLACK);
                    }
                    if(cena == cenaTerminou){
                        DrawText(animal[cagado].fim, 5.5*square, 7.5*square, 25, BLACK);
                    }

                }

                if(capivara.bossDerrotados == 1){
                    DrawTexture(sala[salaAranhas].textura, sala[salaAranhas].frame.x, sala[salaAranhas].frame.y, DARKGRAY);
                    DrawTextureRec(capivara.textura, (Rectangle) { square*(((int)(Timer))%2), desenho_skin, square, square}, (Vector2){ capivara.frame.x, capivara.frame.y}, RAYWHITE); 
                    DrawTextureRec(animal[aranha].textura, (Rectangle) { square*(((int)(Timer))%2), square/3, square, square}, animal->frame, RAYWHITE);
                    DrawRectangle(5*square, 7*square, 2*square, square, WHITE);
                    
                    if(cena == introducao){
                        DrawText(animal[aranha].intro, 5.5*square, 7.5*square, 25, BLACK);
                    }
                    if(cena == agradecimento){
                        DrawText(animal[aranha].arigato, 5.5*square, 7.5*square, 25, BLACK);
                    }
                    if(cena == itemDado){
                        DrawText(animal[aranha].itemNovo, 5.5*square, 7.5*square, 25, BLACK);
                    }
                    if(cena == itemMostrado){
                        DrawTexture(sala[salaAranhas].textura, sala->frame.x, sala[salaAranhas].frame.y, DARKGRAY);
                        DrawTextureRec(capivara.textura, (Rectangle) { 0, desenho_skin, square, square}, (Vector2){ capivara.frame.x, capivara.frame.y}, GRAY);
                        DrawTextureRec(animal[aranha].textura, (Rectangle) { 0, square/3, square, square}, animal[aranha].frame, GRAY);
                        DrawTextureRec(item.textura, (Rectangle) { 0, 0, square, square}, item.frame, RAYWHITE);
                        DrawRectangle(5*square, 7*square, 2*square, square, WHITE);
                        DrawText(animal[aranha].item->nome, 5.5*square, 7.5*square, 25, BLACK);
                    }
                    if(cena == cenaTerminou){
                        DrawText(animal[aranha].fim, 5.5*square, 7.5*square, 25, BLACK);
                    }
                    
                }

                if(capivara.bossDerrotados == 2){
                    DrawTexture(sala[salaGalinha].textura, sala[salaGalinha].frame.x, sala[salaGalinha].frame.y, DARKGRAY);
                    DrawTextureRec(capivara.textura, (Rectangle) { square*(((int)(Timer))%2), desenho_skin, square, square}, (Vector2){ capivara.frame.x, capivara.frame.y}, RAYWHITE);
                    DrawTextureRec(animal[galinha].textura, (Rectangle) { square*(((int)(Timer))%2), square/3, square, square}, animal->frame, RAYWHITE);
                    DrawRectangle(5*square, 7*square, 2*square, square, WHITE);

                    if(cena == introducao){
                        DrawText(animal[galinha].intro, 5.5*square, 7.5*square, 25, BLACK);
                    }
                    if(cena == agradecimento){
                        DrawText(animal[galinha].arigato, 5.5*square, 7.5*square, 25, BLACK);
                    }
                    if(cena == itemDado){
                        DrawText(animal[galinha].itemNovo, 5.5*square, 7.5*square, 25, BLACK);
                    }
                    if(cena == itemMostrado){
                        DrawTexture(sala[salaGalinha].textura, sala->frame.x, sala[salaGalinha].frame.y, DARKGRAY);
                        DrawTextureRec(capivara.textura, (Rectangle) { 0, desenho_skin, square, square}, (Vector2){ capivara.frame.x, capivara.frame.y}, GRAY);
                        DrawTextureRec(animal[galinha].textura, (Rectangle) { 0, square/3, square, square}, animal[galinha].frame, GRAY);
                        DrawTextureRec(item.textura, (Rectangle) { 0, 0, square, square}, item.frame, RAYWHITE);
                        DrawRectangle(5*square, 7*square, 2*square, square, WHITE);
                        DrawText(animal[galinha].item->nome, 5.5*square, 7.5*square, 25, BLACK);
                    }
                    if(cena == cenaTerminou){
                        DrawText(animal[galinha].fim, 5.5*square, 7.5*square, 25, BLACK);
                    }
                    
                }

                if(capivara.bossDerrotados == 3){
                    DrawTexture(sala[salaPeixe].textura, sala[salaPeixe].frame.x, sala[salaPeixe].frame.y, DARKGRAY);
                    DrawTextureRec(capivara.textura, (Rectangle) { square*(((int)(Timer))%2), desenho_skin, square, square}, (Vector2){ capivara.frame.x, capivara.frame.y}, RAYWHITE);
                    DrawTextureRec(animal[peixe].textura, (Rectangle) { square*(((int)(Timer))%2), square/3, square, square}, animal->frame, RAYWHITE);
                    DrawRectangle(5*square, 7*square, 2*square, square, WHITE);

                    if(cena == introducao){
                        DrawText(animal[peixe].intro, 5.5*square, 7.5*square, 25, BLACK);
                    }
                    if(cena == agradecimento){
                        DrawText(animal[peixe].arigato, 5.5*square, 7.5*square, 25, BLACK);
                    }
                    if(cena == itemDado){
                        DrawText(animal[peixe].itemNovo, 5.5*square, 7.5*square, 25, BLACK);
                    }
                    if(cena == itemMostrado){
                        DrawTexture(sala[salaPeixe].textura, sala->frame.x, sala[salaPeixe].frame.y, DARKGRAY);
                        DrawTextureRec(capivara.textura, (Rectangle) { 0, desenho_skin, square, square}, (Vector2){ capivara.frame.x, capivara.frame.y}, GRAY);
                        DrawTextureRec(animal[peixe].textura, (Rectangle) { 0, square/3, square, square}, animal[peixe].frame, GRAY);
                        DrawTextureRec(item.textura, (Rectangle) { 0, 0, square, square}, item.frame, RAYWHITE);
                        DrawRectangle(5*square, 7*square, 2*square, square, WHITE);
                        DrawText(animal[peixe].item->nome, 5.5*square, 7.5*square, 25, BLACK);
                    }
                    if(cena == cenaTerminou){
                        DrawText(animal[peixe].fim, 5.5*square, 7.5*square, 25, BLACK);
                    }

                }
                
                //desenho da cena com os boss
                /*
                if(capivara.bossDerrotados == 0){

                }
                if(capivara.bossDerrotados == 1){
                    
                }
                if(capivara.bossDerrotados == 2){
                    
                }
                if(capivara.bossDerrotados == 3){
                    
                }
                */
            }

            capivara.interacao.interagindo = (IsKeyDown(KEY_Z)) ? 1 : 0;

            fixCollision(&capivara, &(sala[salaAtual]));
            updateInteracaoHitbox(&capivara);
            updateLendoPlaca(&capivara, &(sala[salaAtual]), &pausado, &lendoPlaca, &lendo);
            updateRoom(&capivara, &(sala[salaAtual]));
            updatePorta(&capivara, &sala[capivara.salaAtual]);
            //tem algo de errado
            if(IsKeyPressed(KEY_X) && pausado && !lendo){ updateDialogo(&cena); }

            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTextureRec(Fundo,(Rectangle){0, 0, screenWidth, screenHeight}, (Vector2){0, 0}, RAYWHITE);

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

            // desenha objetos
            for (int i = 0; i < sala[salaAtual].qtdObjetos; i++){
                DrawRectangle(sala[salaAtual].objeto[i].hitbox.x, sala[salaAtual].objeto[i].hitbox.y,
                            sala[salaAtual].objeto[i].hitbox.width, sala[salaAtual].objeto[i].hitbox.height,
                            (CheckCollisionRecs(sala[salaAtual].objeto[i].hitbox, capivara.hitbox)) ? SKYBLUE : DARKBLUE);
                if (capivara.interacao.interagindo){
                    DrawRectangle(sala[salaAtual].objeto[i].hitbox.x, sala[salaAtual].objeto[i].hitbox.y,
                                  sala[salaAtual].objeto[i].hitbox.width, sala[salaAtual].objeto[i].hitbox.height,
                                  (CheckCollisionRecs(sala[salaAtual].objeto[i].hitbox, capivara.interacao.hitbox)) ? SKYBLUE : DARKBLUE);
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
            if (!pausado) { par = ((int)GetTime())%3; }
            DrawTexture(sala[salaAtual].textura, sala[salaAtual].frame.x, sala[salaAtual].frame.y, (pausado) ? DARKGRAY : WHITE);
            for (int i = 0; i < 4; i++){
                if (sala[salaAtual].porta[i].temTextura && !(sala[salaAtual].porta[i].aberta)){
                    DrawTexture(sala[salaAtual].porta[i].textura, sala[salaAtual].porta[i].hitbox.x, sala[salaAtual].porta[i].hitbox.y, RAYWHITE);
                }
            }
            if (capivara.temChave){
                DrawTextureRec(chaves, (Rectangle){0.0f, 64.0f*numeroDaChave, 64.0f, 64.0f},
                               (Vector2){sala[salaJardim].frame.x + 16.0f, sala[salaJardim].frame.y + 16.0f}, RAYWHITE);
            }
            DrawTextureRec(capivara.textura, (Rectangle) {(desenho_capivara - square) + (square * par), desenho_skin, square, square},
                           capivara.frame, (pausado) ? DARKGRAY : WHITE);
            if (lendo){
                for (int i = 0; i < sala[salaAtual].qtdObjetos && interagindoCom == -1; i++){
                    if(CheckCollisionRecs(sala[salaAtual].objeto[i].hitbox, capivara.interacao.hitbox)){
                        interagindoCom = i;
                    }
                }
                if (lendoPlaca){
                    //DrawRectangle(sala[salaAtual].frame.x + 2*square, sala[salaAtual].frame.y + 2*square, 8*square, 6*square, RAYWHITE);
                    DrawTexture(texturaPlaca, sala[salaAtual].frame.x + 2*square, sala[salaAtual].frame.y + 2*square, RAYWHITE);
                    DrawText(sala[salaAtual].objeto[interagindoCom].mensagem, sala[salaAtual].frame.x + 2.25*square + 15, sala[salaAtual].frame.y + 2.25*square, 25, GOLD);
                }
                else if (!lendoPlaca) {
                    //DrawRectangle(sala[salaAtual].frame.x + 2*square, sala[salaAtual].frame.y + 7*square, 8*square, 2*square, RAYWHITE);
                    DrawTexture(texturaLendo, sala[salaAtual].frame.x + 2*square, sala[salaAtual].frame.y + 7*square, RAYWHITE);
                    DrawText(sala[salaAtual].objeto[interagindoCom].mensagem, sala[salaAtual].frame.x + 2.25*square + 15, sala[salaAtual].frame.y + 7.375*square, 50, BLACK);
                }
            }
            interagindoCom = -1;
            if (prevGameMode == combate){ prevGameMode = explorando; }
            capivara.prevHitbox = capivara.hitbox;
            EndDrawing();

            gameMode = updateBossfight(&capivara, &(sala[salaAtual]), &musicaCombate);
            if (gameMode == combate){ prevGameMode = explorando; round = escolherAtaqueCapivara; }
            if (IsKeyPressed(KEY_X)){ pausado = 0; lendoPlaca = 0; lendo = 0; }
            if (IsKeyPressed(KEY_Q)){ gameMode = menu; prevGameMode = explorando; }
        }
//-----------------------------------------------------------------COMBATE------------------------------------------------------------------
        else if (gameMode == combate){
            
            UpdateMusicStream(musicaCombate);
            PlayMusicStream(musicaCombate);
            SetMusicVolume(musicaCombate, 0.2);

            int selecionado = capivara.ataqueSelecionado;
            int bossAtual = capivara.bossDerrotados;
            int animalAtual = bossAtual;

            sprintf(vidaExibidaCapivara, "%2d/%2d", capivara.vida, capivara.vidaMaxima);
            sprintf(vidaExibidaBoss, "%2d/%2d", boss[bossAtual].vida, boss[bossAtual].vidaMaxima);

            BeginDrawing();
            ClearBackground(WHITE);
            
            if (round == escolherAtaqueCapivara && capivara.vida > 0){
                if (IsKeyPressed(KEY_DOWN) && selecionado < 3 &&  capivara.ataque[selecionado + 1].desbloqueado){ capivara.ataqueSelecionado++; }

                if (IsKeyPressed(KEY_UP) && selecionado > 0 &&  capivara.ataque[selecionado - 1].desbloqueado){ capivara.ataqueSelecionado--; }

                if (IsKeyPressed(KEY_Z)){
                    if (capivara.ataque[selecionado].usos > 0){
                        if (capivara.ataque[selecionado].dano > 0){ // mostrarAtaqueCapivara
                            ataqueCritico = GetRandomValue(0, 99);
                            ataqueCritico = (ataqueCritico < capivara.ataque[selecionado].chanceDeCritico) ? 2 : 1;
                            boss[bossAtual].vida -= (ataqueCritico)*capivara.ataque[selecionado].dano;
                            round = (ataqueCritico == 2) ? ataqueCriticoCapivara : mostrarAtaqueCapivara;
                        }
                        else{ // mostrarCuraCapivara
                            capivara.vida -= capivara.ataque[selecionado].dano;
                            sprintf(scene, "%s usou %s!\n%s recuperou %d de vida", capivara.nome, capivara.ataque[selecionado].nome, capivara.nome,
                                    (-1)*capivara.ataque[selecionado].dano);
                            round = mostrarCuraCapivara;
                        }
                        capivara.ataque[selecionado].usos--;
                    
                    }
                    else{ // escolheuErrado
                        sprintf(scene, "você não tem mais usos para esse Ataque!");                       
                        round = escolheuErrado;
                    }
                }
            }

            if (capivara.vida < 0){ capivara.vida = 0; }
            if (round == escolherAtaqueCapivara && capivara.vida == 0){
                sprintf(scene, "Você morreu!\nTente novamente...");
                round = mostrarCapivaraMorreu;
            }

            if (round == ataqueCriticoCapivara){
                sprintf(scene, "Um ataque crítico!");
                round = mostrarCriticoCapivara;
            }

            if (round == mostrarAtaqueCapivara){
                sprintf(scene, "%s usou %s!\n%s levou %d de dano", capivara.nome, capivara.ataque[selecionado].nome,
                        boss[bossAtual].nome, capivara.ataque[selecionado].dano*(ataqueCritico));
            }

            if (round == escolherAtaqueBoss && boss[bossAtual].vida > 0){
                ataqueDoBoss = GetRandomValue(0, 3);
                if (boss[bossAtual].ataque[ataqueDoBoss].dano >= 0){ // mostrarAtaqueBoss
                    capivara.vida -= boss[bossAtual].ataque[ataqueDoBoss].dano;
                    sprintf(scene, "%s usou %s!\n%s levou %d de dano", boss[bossAtual].nome, boss[bossAtual].ataque[ataqueDoBoss].nome,
                            capivara.nome, boss[bossAtual].ataque[ataqueDoBoss].dano);
                    round = mostrarAtaqueBoss;
                }
                else{ // mostrarCuraBoss
                    boss[bossAtual].vida -= boss[bossAtual].ataque[ataqueDoBoss].dano;
                    sprintf(scene, "%s usou %s!\n%s recuperou %d de vida", boss[bossAtual].nome, boss[bossAtual].ataque[ataqueDoBoss].nome,
                            boss[bossAtual].nome, (-1)*boss[bossAtual].ataque[ataqueDoBoss].dano);
                    round = mostrarCuraBoss;                    
                }
            }

            if (boss[bossAtual].vida < 0){ boss[bossAtual].vida = 0; }
            if (round == escolherAtaqueBoss && boss[bossAtual].vida == 0){
                sprintf(scene, "Parabéns! Você derrotou\n%s", boss[bossAtual].nome);
                round = mostrarBossMorreu;
            }

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

            if (round == escolherAtaqueCapivara){
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
                DrawText(scene, arena.frame.x, arena.frame.y + 7*square, 40, BLACK);
            }

            
            */
            // -----------------------------------------------DEBUG DE HUD------------------------------------------------------------------

            if (round == escolherAtaqueCapivara && capivara.vida > 0){
                DrawTexture(arena.texturaEscolherAtaque, arena.frame.x, arena.frame.y, RAYWHITE);
                for (int i = 0; i < 4; i++){
                    if (capivara.ataque[i].desbloqueado){ sprintf(ataqueExibido, "%s", capivara.ataque[i].nome); }
                    else{ sprintf(ataqueExibido, "-"); }
                    DrawText(ataqueExibido, capivara.ataque[i].frame.x, capivara.ataque[i].frame.y + 0.1875*square, 30, BLACK);
                }
                DrawTriangle((Vector2){capivara.ataque[selecionado].frame.x - 0.75*square, capivara.ataque[selecionado].frame.y + 8.0f},
                             (Vector2){capivara.ataque[selecionado].frame.x - 0.75*square, capivara.ataque[selecionado].frame.y + 52.0f},
                             (Vector2){capivara.ataque[selecionado].frame.x - 0.4*square, capivara.ataque[selecionado].frame.y + 30.0f},
                             BLACK);
                DrawTriangle((Vector2){capivara.ataque[selecionado].frame.x + 6.6*square, capivara.ataque[selecionado].frame.y + 8.0f},
                             (Vector2){capivara.ataque[selecionado].frame.x + 6.25*square, capivara.ataque[selecionado].frame.y + 30.0f},
                             (Vector2){capivara.ataque[selecionado].frame.x + 6.6*square, capivara.ataque[selecionado].frame.y + 52.0f},
                             BLACK);
                if (capivara.ataque[selecionado].dano > 0 ){ sprintf(danoDoAtaque, "%2d de dano", capivara.ataque[selecionado].dano); }
                else{ sprintf(danoDoAtaque, "%2d de cura", (-1)*capivara.ataque[selecionado].dano); }
                DrawText(danoDoAtaque, arena.ataqueInfo.x + arena.ataqueInfo.width/2.0f - MeasureText(danoDoAtaque, 42)/2.0f,
                         arena.ataqueInfo.y + 0.2*square, 42, BLACK);

                sprintf(usosDoAtaque, "%d/%d", capivara.ataque[selecionado].usos, capivara.ataque[selecionado].usosMaximo);
                DrawText(usosDoAtaque, arena.ataqueInfo.x + arena.ataqueInfo.width/2.0f - MeasureText(usosDoAtaque, 42)/2.0f,
                         arena.ataqueInfo.y + 1*square, 42, BLACK);

                sprintf(chanceDeCritico, "%d%% de chance\n", capivara.ataque[selecionado].chanceDeCritico);
                DrawText(chanceDeCritico, arena.ataqueInfo.x + arena.ataqueInfo.width/2.0f - MeasureText(chanceDeCritico, 42)/2.0f,
                         arena.ataqueInfo.y + 1.7*square, 42, BLACK);
                sprintf(chanceDeCritico, "de critico");
                DrawText(chanceDeCritico, arena.ataqueInfo.x + arena.ataqueInfo.width/2.0f - MeasureText(chanceDeCritico, 42)/2.0f,
                         arena.ataqueInfo.y + 2.1*square, 42, BLACK);
                DrawText("Aperte z para escolher o ataque", arena.frame.x + 0.25*square, arena.frame.y + 0.25*square, 20, DARKBROWN);
            }
            else{
                DrawTexture(arena.texturaDescricao, arena.frame.x, arena.frame.y, RAYWHITE);
                DrawText(scene, arena.frame.x + 0.25*square, arena.frame.y + 7.25*square, 50, BLACK);
                DrawText("aperte x para passar", arena.frame.x + 5.75*square, arena.frame.y + 9.25*square, 50, BLACK);
            }

            //desenho do animal
            DrawTextureRec(animal[animalAtual].textura, (Rectangle){0, 0, square, square}, 

                          (Vector2){arena.animalInfo.frame.x, arena.animalInfo.frame.y}, RAYWHITE);
            DrawTextureRec(boss[bossAtual].textura, (Rectangle){0, 0, 3*square, 3*square}, 
                          (Vector2){arena.bossInfo.frame.x + 0.5*square, arena.bossInfo.frame.y - 0.125*square}, RAYWHITE);
            DrawTextureRec(capivara.texturaCombate, (Rectangle){0, desenho_skin_combate, 3.5*square, 3*square},
                          (Vector2){arena.capivaraInfo.frame.x, arena.capivaraInfo.frame.y}, RAYWHITE);
            DrawText(capivara.nome, arena.capivaraInfo.nomeFrame.x, arena.capivaraInfo.nomeFrame.y, 40, BLACK);
            DrawText(vidaExibidaCapivara, arena.capivaraInfo.vidaFrame.x, arena.capivaraInfo.vidaFrame.y, 40, BLACK);
            DrawText(boss[bossAtual].nome, arena.bossInfo.nomeFrame.x, arena.bossInfo.nomeFrame.y, 40, BLACK);
            DrawText(vidaExibidaBoss, arena.bossInfo.vidaFrame.x, arena.bossInfo.vidaFrame.y, 40, BLACK);

            EndDrawing();

            if (IsKeyPressed(KEY_X)){ updateRound(&round, &capivara, &desenho_skin, &desenho_skin_combate, &gameMode, &pausado); }

            if (IsKeyPressed(KEY_Q)){ gameMode = menu; prevGameMode = combate; }
        }
//-----------------------------------------------------------------GAMEOVER-----------------------------------------------------------------
        else if (gameMode == gameOver){
            // Reload
            loadCapivaraExplorando(&capivara, screenWidth, screenHeight);
            loadCapivaraCombate(&capivara, &arena);

            loadBoss1(&(boss[0])); boss[0].textura.width *= 9.0f; boss[0].textura.height *= 9.0f;
            loadBoss2(&(boss[1])); boss[1].textura.width *= 9.0f; boss[1].textura.height *= 9.0f;
            loadBoss3(&(boss[2])); boss[2].textura.width *= 9.0f; boss[2].textura.height *= 9.0f;
            loadBoss4(&(boss[3])); boss[3].textura.width *= 9.0f; boss[3].textura.height *= 9.0f;

            for (int i = 0; i < 6; i++){ loadSalas(&(sala[i]), screenWidth, screenHeight); }
            loadSala1(&(sala[salaJardim]));
            if (sala[salaJardim].objeto == NULL){
                for (int i = 0; i < 1; i++){ unloadSalas(&(sala[i])); printf("Erro de alocacao\n"); exit(1); }
            }
            loadSala2(&(sala[salaHub]));
            if (sala[salaHub].objeto == NULL){
                for (int i = 0; i < 2; i++){ unloadSalas(&(sala[i])); printf("Erro de alocacao\n"); exit(1); }
            }
            loadSala3(&(sala[salaCagado]));
            if (sala[salaCagado].objeto == NULL){
                for (int i = 0; i < 3; i++){ unloadSalas(&(sala[i])); printf("Erro de alocacao\n"); exit(1); }
            }
            loadSala4(&(sala[salaAranhas]));
            if (sala[salaAranhas].objeto == NULL){
                for (int i = 0; i < 4; i++){ unloadSalas(&(sala[i])); printf("Erro de alocacao\n"); exit(1); }
            }
            loadSala5(&(sala[salaGalinha]));
            if (sala[salaGalinha].objeto == NULL){
                for (int i = 0; i < 5; i++){ unloadSalas(&(sala[i])); printf("Erro de alocacao\n"); exit(1); }
            }
            loadSala6(&(sala[salaPeixe]));
            if (sala[salaPeixe].objeto == NULL){
                for (int i = 0; i < 6; i++){ unloadSalas(&(sala[i])); printf("Erro de alocacao\n"); exit(1); }
            }

            gameMode = menu; prevGameMode = explorando;
            par = 0;
            pausado = false; lendo = false; lendoPlaca = false;
            round = escolherAtaqueCapivara;
            desenho_skin = 0; desenho_skin_combate = 0;
        }
    }

    //UNLOADS // FREES
    UnloadTexture(capivara.textura);
    UnloadTexture(item.textura);
    UnloadTexture(chaves);
    for (int i = 0; i < 4; i++){ UnloadTexture(boss[i].textura); }
    for (int i = 0; i < 4; i++){ UnloadTexture(animal[i].textura); }
    for (int i = 0; i < 6; i++){ unloadSalas(&(sala[i])); }
    unloadArena(&arena);
    UnloadMusicStream(musica);
    UnloadTexture(capivara.texturaCombate);
    
    CloseAudioDevice();
    CloseWindow();
    return 0;
}