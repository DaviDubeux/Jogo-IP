#include <stdio.h>
#include <stdlib.h>
#include "C:\raylib\raylib\src\raylib.h"
#include "defines.h"
#include "personagens.h"
#include "salas.h"
#include "explorando.h"
#include "combate.h"

int main(){
    //menu
    int gameMode = menu;
    int prevGameMode = explorando;
    
    //explorando
    int par = 0;
    bool ganhou = false;
    bool pausado = false;
    bool lendoPlaca = false;
    bool lendo = false;
    int interagindoCom;
    Texture2D chaveCagado, chaveAranhas, chaveGalinha, chavePeixe;

    //combate
    int round = escolherAtaqueCapivara;
    bool semAtaques = false;
    int ataqueCritico = 0;
    char vidaExibidaCapivara[10] = "";
    char vidaExibidaBoss[10] = "";
    char ataqueExibido[50] = "";
    int ataqueDoBoss = 0;
    char scene[100] = "";
    char danoDoAtaque[10] = "";
    char usosDoAtaque[10] = "";
    char chanceDeCritico[10] = "";
    Texture2D objetos[4];

    //menu
    Texture2D Controles, Creditos, Menu, Fundo;
    int tela = 0;
    int controles = 0;
    int creditos = 0;

    //musica
    Music musica;
    Music musicaCombate;

    InitWindow(1920, 1080, "Missão IBAMA: Contra-Ataque a Thalya");
    InitAudioDevice();
    SetMasterVolume(5.0);
    if (!IsWindowFullscreen()){ ToggleFullscreen(); }
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

    chaveCagado = LoadTexture("./assets/cenarios/explorando/chaveCagado.png");
    chaveAranhas = LoadTexture("./assets/cenarios/explorando/chaveAranhas.png");
    chaveGalinha = LoadTexture("./assets/cenarios/explorando/chaveGalinha.png");
    chavePeixe = LoadTexture("./assets/cenarios/explorando/chavePeixe.png");

    objetos[0] = LoadTexture("./assets/cut_scenes/escudo.png");
    objetos[0].width *= 4; objetos[0].height *= 4;    
    objetos[1] = LoadTexture("./assets/cut_scenes/bandaid.png");
    objetos[1].width *= 4; objetos[1].height *= 4;    
    objetos[2] = LoadTexture("./assets/cut_scenes/mochila.png");
    objetos[2].width *= 4; objetos[2].height *= 4;    
    objetos[3] = LoadTexture("./assets/cut_scenes/coroa.png");
    objetos[3].width *= 4; objetos[3].height *= 4;    

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
            
            BeginDrawing();
            ClearBackground(DARKBLUE);

            if(controles == 0 && creditos == 0){ tela = 0; }
            if(IsKeyPressed(KEY_W) && creditos == 0){ tela = 1; }
            if(IsKeyPressed(KEY_E) && controles == 0){ tela = 2; }

            //Entrar no jogo
            if(tela == 0){ //tela inicial
                DrawTextureRec(Menu,(Rectangle){0, 0, screenWidth, screenHeight}, (Vector2){0, 0}, RAYWHITE);
            }
            if(tela == 1){ //tela de controles 
                controles = 1;
                DrawTextureRec(Controles,(Rectangle){0, 0, screenWidth, screenHeight}, (Vector2){ 0, 0}, RAYWHITE);
                if(IsKeyPressed(KEY_B)){ controles = 0; }
            }
            if(tela == 2){ //tela de créditos
                creditos = 1;
                DrawTextureRec(Creditos,(Rectangle){0, 0, screenWidth, screenHeight}, (Vector2){ 0, 0}, RAYWHITE);
                if(IsKeyPressed(KEY_B)){ creditos = 0; }
            }

            EndDrawing();

            if (IsKeyPressed(KEY_Q)){ gameMode = prevGameMode; }
        }
//----------------------------------------------------------------EXPLORANDO----------------------------------------------------------------
        else if (gameMode == explorando){
            //pra mover o player
            double delta = GetTime() - time;
            time = GetTime();

            int salaAtual = capivara.salaAtual;

            //por a música do jardim
            if (salaAtual == salaJardim){ UpdateMusicStream(sala[salaJardim].musica); }
            //por a música dos quartos
            else{ UpdateMusicStream(sala[salaHub].musica); }
            PlayMusicStream(sala[salaAtual].musica);
            SetMusicVolume(sala[salaAtual].musica, 1.0f);

            //move o player se não estiver pausado
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
            
            //checa se o player está interagindo
            capivara.interacao.interagindo = (IsKeyDown(KEY_Z)) ? 1 : 0;

            //funções do gameMode explorando:
            fixCollision(&capivara, &(sala[salaAtual])); //conserta a colisão
            updateInteracaoHitbox(&capivara); //atualiza para a hitbox de interacão ficar onde o player está olhando
            updateLendo(&capivara, &(sala[salaAtual]), &pausado, &lendoPlaca, &lendo); //checa se o player está lendo algo
            updateRoom(&capivara, &(sala[salaAtual])); //muda a sala do player
            updatePorta(&capivara, &sala[salaAtual]); //abre as portas se o player tiver a chave

            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTextureRec(Fundo,(Rectangle){0, 0, screenWidth, screenHeight}, (Vector2){0, 0}, RAYWHITE); //bota um fundo do ibama

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


            //anima a capivara normalmente desde o último movimento
            if (!pausado) { par = ((int)GetTime())%3; }

            //desenha a sala
            DrawTexture(sala[salaAtual].textura, sala[salaAtual].frame.x, sala[salaAtual].frame.y, (pausado) ? DARKGRAY : WHITE);
            //desenha as portas trancadas
            for (int i = 0; i < 4; i++){
                if (sala[salaAtual].porta[i].temTextura && !(sala[salaAtual].porta[i].aberta)){
                    DrawTexture(sala[salaAtual].porta[i].textura, sala[salaAtual].porta[i].hitbox.x, sala[salaAtual].porta[i].hitbox.y,
                    (pausado) ? DARKGRAY : WHITE);
                }
            }
            //desenha a chave atual do player
            if (capivara.temChave){
                if (capivara.chaves == 0){
                    DrawTexture(chaveCagado, sala[salaJardim].frame.x + 16.0f, sala[salaJardim].frame.y + 16.0f, RAYWHITE);
                }
                if (capivara.chaves == 1){
                    DrawTexture(chaveAranhas, sala[salaJardim].frame.x + 16.0f, sala[salaJardim].frame.y + 16.0f, RAYWHITE);
                }
                if (capivara.chaves == 2){
                    DrawTexture(chaveGalinha, sala[salaJardim].frame.x + 16.0f, sala[salaJardim].frame.y + 16.0f, RAYWHITE);
                }
                if (capivara.chaves == 3){
                    DrawTexture(chavePeixe, sala[salaJardim].frame.x + 16.0f, sala[salaJardim].frame.y + 16.0f, RAYWHITE);
                }

            }
            //desenha o player
            DrawTextureRec(capivara.textura, (Rectangle) {(desenho_capivara - square) + (square * par), desenho_skin, square, square},
                           capivara.frame, (pausado) ? DARKGRAY : WHITE);
            //desenha a placa do jardim ou o pensamento do player
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
            //checa se o player ganhou o jogo
            if (capivara.bossDerrotados == 4){ ganhou = true; pausado = true; }
            if (ganhou){
                DrawTexture(texturaLendo, sala[salaAtual].frame.x + 2*square, sala[salaAtual].frame.y + 7*square, RAYWHITE);
                DrawText("Parabéns! Você salvou os animais\ndas garras de Thalya!",
                         sala[salaAtual].frame.x + 2.25*square + 15, sala[salaAtual].frame.y + 7.375*square, 40, BLACK);
            }
            EndDrawing();
            
            //atualiza a prevHitbox para a função fixCollision
            capivara.prevHitbox = capivara.hitbox;
            //checa se o player vai entrar em combate
            gameMode = updateBossfight(&capivara, &(sala[salaAtual]), &musicaCombate);
            if (gameMode == combate){ prevGameMode = explorando; round = escolherAtaqueCapivara; }

            //passa o diálogo e abre o menu
            if (IsKeyPressed(KEY_X) && !ganhou){ pausado = 0; lendoPlaca = 0; lendo = 0; }
            if (IsKeyPressed(KEY_X) && ganhou){ gameMode = restart; }
            if (IsKeyPressed(KEY_Q)){ gameMode = menu; prevGameMode = explorando; }
        }
//-----------------------------------------------------------------COMBATE------------------------------------------------------------------
        else if (gameMode == combate){
            //musica do combate
            UpdateMusicStream(musicaCombate);
            PlayMusicStream(musicaCombate);
            SetMusicVolume(musicaCombate, 0.2);

            //para simplificar na leitura/escrita
            int selecionado = capivara.ataqueSelecionado;
            int bossAtual = capivara.bossDerrotados;
            int animalAtual = bossAtual;

            //atualiza a vida do player e do boss na arena
            sprintf(vidaExibidaCapivara, "%2d/%2d", capivara.vida, capivara.vidaMaxima);
            sprintf(vidaExibidaBoss, "%2d/%2d", boss[bossAtual].vida, boss[bossAtual].vidaMaxima);

            BeginDrawing();
            ClearBackground(WHITE);
            DrawTextureRec(Fundo,(Rectangle){0, 0, screenWidth, screenHeight}, (Vector2){0, 0}, RAYWHITE);
            
            //precessa em qual round o combate está
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
                    else{
                        semAtaques = true;
                        for (int i = 0; i < 4 && semAtaques; i++){
                            if (capivara.ataque[i].usos > 0){ semAtaques = false; }
                        }
                        if (semAtaques){ // não tem mais ataques
                            sprintf(scene, "você não tem mais ataques");
                            round = acabaramOsUsos;
                        }
                        else{ // escolheuErrado
                            sprintf(scene, "você não tem mais usos para esse Ataque!");
                            round = escolheuErrado;
                        }
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

            if (round == escolherIntroAnimal){
                sprintf(scene, animal[bossAtual].intro);
                round = mostrarIntroAnimal;
            }

            if (round == escolherAgradecimentoAnimal){
                sprintf(scene, animal[bossAtual].arigato);
                round = mostrarAgradecimentoAnimal;
            }

            if (round == escolherItemDado){
                sprintf(scene, animal[bossAtual].itemNovo);
                round = mostrarItemDado;
            }

            if (round == escolherFimDialogo){
                sprintf(scene, animal[bossAtual].fim);
                round = mostrarFimDialogo;
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

            //desenha a arena
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
                DrawTexture(arena.texturaDescricao, arena.frame.x, arena.frame.y, (round > mostrarBossMorreu) ? DARKGRAY : RAYWHITE);
                DrawTexture(arena.texturaParteDeBaixo, arena.frame.x, arena.frame.y, RAYWHITE);
                DrawText(scene, arena.frame.x + 0.25*square, arena.frame.y + 7.25*square, 50, BLACK);
                DrawText("aperte x para passar", arena.frame.x + 5.75*square, arena.frame.y + 9.25*square, 50, BLACK);
            }

            //desenho dos personagens
            DrawTextureRec(animal[animalAtual].textura, (Rectangle){0, 0, square, square}, 
                          (Vector2){arena.animalInfo.frame.x, arena.animalInfo.frame.y}, RAYWHITE);
            DrawTextureRec(boss[bossAtual].textura, (Rectangle){0, 0, 3*square, 3*square}, 
                          (Vector2){arena.bossInfo.frame.x + 0.5*square, arena.bossInfo.frame.y - 0.125*square},
                          (round > mostrarBossMorreu) ? DARKGRAY : RAYWHITE);
            DrawTextureRec(capivara.texturaCombate, (Rectangle){0, desenho_skin_combate, 3.5*square, 3*square},
                          (Vector2){arena.capivaraInfo.frame.x, arena.capivaraInfo.frame.y},
                          (round > mostrarBossMorreu) ? DARKGRAY : RAYWHITE);
            DrawText(capivara.nome, arena.capivaraInfo.nomeFrame.x, arena.capivaraInfo.nomeFrame.y, 40, BLACK);
            DrawText(vidaExibidaCapivara, arena.capivaraInfo.vidaFrame.x, arena.capivaraInfo.vidaFrame.y, 40, BLACK);
            if (round <= mostrarBossMorreu){
                DrawText(boss[bossAtual].nome, arena.bossInfo.nomeFrame.x, arena.bossInfo.nomeFrame.y, 40, BLACK);
                DrawText(vidaExibidaBoss, arena.bossInfo.vidaFrame.x, arena.bossInfo.vidaFrame.y, 40, BLACK);
            }
            else{
                DrawText(animal[bossAtual].nome, arena.bossInfo.nomeFrame.x, arena.bossInfo.nomeFrame.y, 40, BLACK);
            }
            if (round == mostrarItemDado){
                DrawTextureRec(objetos[bossAtual], (Rectangle){0.0f, (float)(capivara.bossDerrotados)*4*square, 4*square, 4*square},
                              (Vector2){arena.frame.x + 4*square, arena.frame.y + 3*square}, RAYWHITE);
            }

            EndDrawing();

            //passa o diálogo e abre o menu
            if (IsKeyPressed(KEY_X)){ updateRound(&round, &capivara, &desenho_skin, &desenho_skin_combate, &gameMode, &pausado); }
            if (IsKeyPressed(KEY_Q)){ gameMode = menu; prevGameMode = combate; }
        }
//-----------------------------------------------------------------restart-----------------------------------------------------------------
        else if (gameMode == restart){
            //reseta o jogo para o player jogar novamente
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
            
            chaveCagado = LoadTexture("./assets/cenarios/explorando/chaveCagado.png");
            chaveAranhas = LoadTexture("./assets/cenarios/explorando/chaveAranhas.png");
            chaveGalinha = LoadTexture("./assets/cenarios/explorando/chaveGalinha.png");
            chavePeixe = LoadTexture("./assets/cenarios/explorando/chavePeixe.png");

            gameMode = menu; prevGameMode = explorando;
            par = 0; ganhou = false;
            pausado = false; lendo = false; lendoPlaca = false;
            round = escolherAtaqueCapivara;
            desenho_skin = 0; desenho_skin_combate = 0;
        }
    }

    //UNLOADS / FREES
    UnloadTexture(capivara.textura);
    UnloadTexture(capivara.texturaCombate);
    UnloadTexture(chaveCagado);
    UnloadTexture(chaveAranhas);
    UnloadTexture(chaveGalinha);
    UnloadTexture(chavePeixe);
    UnloadTexture(Controles); UnloadTexture(Menu); UnloadTexture(Creditos); UnloadTexture(Fundo);
    UnloadTexture(texturaPlaca); UnloadTexture(texturaLendo);
    for (int i = 0; i < 4; i++){ UnloadTexture(objetos[i]); }
    for (int i = 0; i < 4; i++){ UnloadTexture(boss[i].textura); }
    for (int i = 0; i < 4; i++){ UnloadTexture(animal[i].textura); }
    for (int i = 0; i < 6; i++){ unloadSalas(&(sala[i])); }
    unloadArena(&arena);
    UnloadMusicStream(musica); UnloadMusicStream(musicaCombate);

    CloseAudioDevice();
    CloseWindow();
    return 0;
}