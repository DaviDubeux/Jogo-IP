#include <stdio.h>
#include <stdlib.h>
#include "C:\raylib\raylib\src\raylib.h"
#include "defines.h"
#include "personagens.h"
#include "salas.h"
#include "colisao.h"
#include "combate.h"

int main(){
    int gameMode = menu;
    int prevGameMode = combate;
    
    //explorando
    int par = 0;
    bool pausado = false;
    bool lendoPlaca = false;

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
    Texture2D setas, wasd, TecX, TecZ, Menu;
    int opcao = 0;
    int opcoes = 0;
    int creditos = 0;

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
    Animal animal[4];
    Sala sala[6];
    Arena arena;

//-------------------------------------------------------------------LOADS-------------------------------------------------------------------
    loadCapivaraExplorando(&capivara, screenWidth, screenHeight);

    loadBoss1(&(boss[0])); boss[0].textura.width *= 9.0f; boss[0].textura.height *= 9.0f;
    loadBoss2(&(boss[1])); boss[1].textura.width *= 9.0f; boss[1].textura.height *= 9.0f;
    loadBoss3(&(boss[2])); boss[2].textura.width *= 9.0f; boss[2].textura.height *= 9.0f;
    loadBoss4(&(boss[3])); boss[3].textura.width *= 9.0f; boss[3].textura.height *= 9.0f;

    loadAnimal1(&(animal[0])); animal[0].textura.width *= 3.0f; animal[0].textura.height *= 3.0f;
    loadAnimal2(&(animal[1])); animal[1].textura.width *= 3.0f; animal[1].textura.height *= 3.0f;
    loadAnimal3(&(animal[2])); animal[2].textura.width *= 3.0f; animal[2].textura.height *= 3.0f;
    loadAnimal4(&(animal[3])); animal[3].textura.width *= 3.0f; animal[3].textura.height *= 3.0f;

    for (int i = 0; i < 6; i++){ loadSalas(&(sala[i]), screenWidth, screenHeight); }
    loadSala1(&(sala[salaJardim]));
    if (sala[salaJardim].obstaculo == NULL){
        for (int i = 0; i < 1; i++){ unloadSalas(&(sala[i])); printf("Erro de alocacao\n"); exit(1); }
    }
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
    if (sala[salaPeixe].obstaculo == NULL){
        for (int i = 0; i < 6; i++){ unloadSalas(&(sala[i])); printf("Erro de alocacao\n"); exit(1); }
    }
    
    loadArena(&arena, screenWidth, screenHeight);
    loadCapivaraCombate(&capivara, &arena);
    
    setas = LoadTexture("./assets/cenarios/menu/setas.png");
    setas.height = 350.0f;
    setas.width = 350.0f;

    wasd = LoadTexture("./assets/cenarios/menu/wasd.png");
    wasd.height = 350.0f;
    wasd.width = 350.0f;

    TecX = LoadTexture("./assets/cenarios/menu/teclax.png");
    TecX.height = 100.0f;
    TecX.width = 100.0f;

    TecZ = LoadTexture("./assets/cenarios/menu/teclaz.png");
    TecZ.height = 100.0f;
    TecZ.width = 100.0f;

    Menu = LoadTexture("./assets/cenarios/menu/Ibama.png");
    Menu.height = screenHeight;
    Menu.width = screenWidth;

    Texture2D texturaPlaca = LoadTexture("./assets/cenarios/explorando/lendoPlaca.png");
    texturaPlaca.width = 8*square; texturaPlaca.height = 6*square;

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
                DrawTextureRec(Menu,(Rectangle){0, 0, 1920, 1080}, (Vector2){0, 0}, RAYWHITE);
                DrawText("Missão IBAMA: Contra-Ataque à Thalya", screenHeight / 2 - MeasureText("Missão IBAMA: Contra-Ataque à Thalya", 20) / 2, 15, 75, LIME);

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
                DrawText("Use as setas do teclado para se movimentar  ou W A S D", 75, 210, 32, WHITE);
                //Z para interagir e X para passar dos dialogos
                DrawTextureRec(wasd,(Rectangle){0, 0, 350, 350}, (Vector2){ 640, 200}, GRAY);
                DrawTextureRec(setas,(Rectangle){0, 0, 350, 350}, (Vector2){ 180, 200}, GRAY);
                DrawTextureRec(TecZ,(Rectangle){0, 0, 100, 100}, (Vector2){ 180, 580}, 
                GRAY);
                DrawTextureRec(TecX,(Rectangle){0, 0, 100, 100}, (Vector2){ 500, 580}, GRAY);

                DrawText("Z para interagir com objetos  \nX para passar dialogos", 100, 750, 36, WHITE);

                DrawText("Pressione B para retornar ao menu", 100, 950, 55, MAROON);

                if(IsKeyPressed(KEY_B)){ opcoes = 0; }
            }
            if(opcao == 2){
                creditos = 1;
                ClearBackground(SKYBLUE);
                DrawText(" Autores:\n Davi Dubeux \n Henrique Carvalho \n J.Pedro Marinho \n Mayres Mauricio Andrey \n Thalya Mayara(Detentora dos direitos da historia) \n Victor Bastos", 80, 210, 50, DARKPURPLE);
                
                DrawText("Pressione B para retornar ao menu", 100, 950, 55, MAROON);
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

            if (capivara.salaAtual == salaJardim){ UpdateMusicStream(sala[salaJardim].musica); }
            else{ UpdateMusicStream(sala[salaHub].musica); }
            PlayMusicStream(sala[salaAtual].musica);
            SetMusicVolume(sala[salaAtual].musica, 1.0f);


            if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && !pausado) {
                capivara.hitbox.y -= capivara.speed * delta;
                updateFrame(&capivara);
                DrawTextureRec(capivara.textura, (Rectangle) {(square*7), desenho_skin, square, square}, capivara.frame, WHITE);
                desenho_capivara = (square * 7);
                capivara.direcao = sentidoCima;
            }

            if ((IsKeyDown(KEY_DOWN)  || IsKeyDown(KEY_S)) && !pausado) {
                capivara.hitbox.y += capivara.speed * delta;
                updateFrame(&capivara);
                DrawTextureRec(capivara.textura, (Rectangle) { (square*10), desenho_skin, square, square}, capivara.frame, WHITE);
                desenho_capivara = (square * 10);
                capivara.direcao = sentidoBaixo;
            }

            if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && !pausado) {
                capivara.hitbox.x += capivara.speed * delta;
                updateFrame(&capivara);
                DrawTextureRec(capivara.textura, (Rectangle) { square, desenho_skin, square, square}, capivara.frame, WHITE);
                desenho_capivara = (square * 1);
                capivara.direcao = sentidoDireita;
            }

            if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && !pausado) {
                capivara.hitbox.x -= capivara.speed * delta;
                updateFrame(&capivara);
                DrawTextureRec(capivara.textura, (Rectangle) {(square*4) , desenho_skin, square, square}, capivara.frame, WHITE);
                desenho_capivara = (square * 4);
                capivara.direcao = sentidoEsquerda;
            }

            capivara.interacao.interagindo = (IsKeyDown(KEY_Z)) ? 1 : 0;

            fixCollision(&capivara, &(sala[salaAtual]));
            updateInteracaoHitbox(&capivara);
            updateLendoPlaca(&capivara, &(sala[salaAtual]), &pausado, &lendoPlaca);
            updateRoom(&capivara, &(sala[salaAtual]));

            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTextureRec(Menu,(Rectangle){0, 0, 1920, 1080}, (Vector2){0, 0}, RAYWHITE);

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

            // desenha placa
            DrawRectangle(sala[salaAtual].placa.hitbox.x, sala[salaAtual].placa.hitbox.y,
                          sala[salaAtual].placa.hitbox.width, sala[salaAtual].placa.hitbox.height,
                          (CheckCollisionRecs(sala[salaAtual].placa.hitbox, capivara.hitbox)) ? SKYBLUE : DARKBLUE);
            if (capivara.interacao.interagindo){
                DrawRectangle(sala[salaAtual].placa.hitbox.x, sala[salaAtual].placa.hitbox.y,
                              sala[salaAtual].placa.hitbox.width, sala[salaAtual].placa.hitbox.height,
                              (CheckCollisionRecs(sala[salaAtual].placa.hitbox, capivara.interacao.hitbox)) ? SKYBLUE : DARKBLUE);
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
            if (sala[salaAtual].placa.hitbox.x != sala[salaAtual].frame.x && sala[salaAtual].placa.hitbox.y != sala[salaAtual].frame.y){
                DrawTextureRec(sala[salaAtual].placa.textura, (Rectangle){0, 0, square, square},
                               (Vector2){sala[salaAtual].placa.hitbox.x, sala[salaAtual].placa.hitbox.y} , (pausado) ? DARKGRAY : WHITE);
            }
            DrawTextureRec(capivara.textura, (Rectangle) {(desenho_capivara - square) + (square * par), desenho_skin, square, square},
                           capivara.frame, (pausado) ? DARKGRAY : WHITE);
            if (lendoPlaca){
                //DrawRectangle(sala[salaAtual].frame.x + 2*square, sala[salaAtual].frame.y + 2*square, 8*square, 6*square, RAYWHITE);
                DrawTexture(texturaPlaca, sala[salaAtual].frame.x + 2*square, sala[salaAtual].frame.y + 2*square, RAYWHITE);
                DrawText(sala[salaAtual].placa.mensagem, sala[salaAtual].frame.x + 2.25*square, sala[salaAtual].frame.y + 2.25*square, 30, YELLOW);
            }
            if (prevGameMode == combate){ prevGameMode = explorando; }
            capivara.prevHitbox = capivara.hitbox;
            EndDrawing();

            gameMode = updateBossfight(&capivara, &(sala[salaAtual]));
            if (gameMode == combate){ prevGameMode = explorando; round = escolherAtaqueCapivara; }
            if (IsKeyPressed(KEY_X)){ pausado = 0; lendoPlaca = 0; }
            if (IsKeyPressed(KEY_Q)){ gameMode = menu; prevGameMode = explorando; }
        }
//-----------------------------------------------------------------COMBATE------------------------------------------------------------------
        else if (gameMode == combate){
            UpdateMusicStream(musicaCombate);
            PlayMusicStream(musicaCombate);
            SetMusicVolume(musicaCombate, 0.2);
            
            int selecionado = capivara.ataqueSelecionado;
            int bossAtual = capivara.bossDerrotados;
            int animalAtual = capivara.animaisResgatados;

            sprintf(vidaExibidaCapivara, "%2d/%2d", capivara.vida, capivara.vidaMaxima);
            sprintf(vidaExibidaBoss, "%2d/%2d", boss[bossAtual].vida, boss[bossAtual].vidaMaxima);

            BeginDrawing();
            ClearBackground(RAYWHITE);
            
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

            /*
            for (int i = 0; i < 6; i++){ loadSalas(&(sala[i]), screenWidth, screenHeight); }
            loadSala1(&(sala[salaJardim]));
            if (sala[salaJardim].obstaculo == NULL){
                for (int i = 0; i < 1; i++){ unloadSalas(&(sala[i])); printf("Erro de alocacao\n"); exit(1); }
            }
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
            if (sala[salaPeixe].obstaculo == NULL){
                for (int i = 0; i < 6; i++){ unloadSalas(&(sala[i])); printf("Erro de alocacao\n"); exit(1); }
            }
            */

            gameMode = menu; prevGameMode = explorando;
            par = 0;
            pausado = false; lendoPlaca = false;
            round = escolherAtaqueCapivara;
        }
    }

    //UNLOADS / FREES
    UnloadTexture(capivara.textura);
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