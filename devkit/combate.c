#include "combate.h"
#include "constants.h"
#include <stdio.h>


//FUNÇõES DO COMBATE

//Realiza o turno dos inimigos
void turnoInimigos(Combate *c){
    Player *p = &c->player;

    // 1. Escudo dos inimigos some
    for (int i = 0; i < c->qtdInimigos; i++) {
        c->inimigos[i].base.shield = 0;
    }
    printf("TURNO DOS INIMIGOS");
    // 2. Cada inimigo executa a ação dele
    for (int i = 0; i < c->qtdInimigos; i++) {
        executarAcao(&c->inimigos[i], p);

        // Se o player morreu, fim imediato
        if (p->base.life <= 0) {
            // aqui você pode colocar flag de game over
            return;
        }
    }

    // 4. Volta para o turno do jogador
    iniciarTurnoPlayer(&c->player);
    c->turno = TURN_PLAYER;
}

// Inicia um novo turno do combate
void novoTurno(Combate *combate){
    Player *player = &combate->player;

    combate->qtdBatalhas++;
    
    player->base.shield = 0;        
    player->energy = 3;             
    player->selectedCarta = 0;
    player->selectedEnemy = 0;
    player->selectedMode  = 0;

    //Descartando a mão do player
    for (int i = 0; i < player->qtdMaoCartas; i++) {
        player->baralhoDescarte.cartas[player->baralhoDescarte.quantity++] = player->mao[i];
    }
    player->qtdMaoCartas = 0;


   //Valida se o baralho de compra tem menos que 5 cartas para reorganizar
    if (player->baralhoCompra.quantity < 5) {
        for (int i = 0; i < player->baralhoDescarte.quantity; i++) {
            player->baralhoCompra.cartas[player->baralhoCompra.quantity++] =
                player->baralhoDescarte.cartas[i];
        }
        player->baralhoDescarte.quantity = 0;

        embaralharBaralho(&player->baralhoCompra);
    }

    //Realiza compra de 5 novas cartas
     comprarCarta(player);


    //gerando 2 novos inimigos
    combate->qtdInimigos = 2;  
    for(int i = 0; i < combate->qtdInimigos; i++) {
        gerarInimigo(&combate->inimigos[i]);
    }

    //Impede a geração de dois inimigos fortes de forma recursiva
    while (combate->inimigos[0].type == 'F' && combate->inimigos[1].type == 'F') {
        gerarInimigo(&combate->inimigos[1]); // repete até ser fraco
    }

    // Turno passa a ser do player
    combate->turno = TURN_PLAYER;
}


// Retirar o inimigo do vetor de inimigos do combate
void removerInimigo(Combate *combate) {
    int idxInimigoSelecionado = combate->player.selectedEnemy;

    for(int i = idxInimigoSelecionado; i < combate->qtdInimigos - 1; i++) {
        combate->inimigos[i] = combate->inimigos[i + 1];
    }
    combate->qtdInimigos--;

    if(combate->player.selectedEnemy >= combate->qtdInimigos) { //Ajustando o índice para que ele fique válido
        combate->player.selectedEnemy = combate->qtdInimigos - 1;
    }

    if(combate->player.selectedEnemy > 0) {
        combate->player.selectedEnemy = 0;
    }
}

// Lógica de atuação de cada carta acionada
void jogarCarta(Combate *c) {
    Player *player = &c->player;

    int idx = player->selectedCarta;
    Carta carta = player->mao[idx];

    // Verifica energia
    if (player->energy < carta.custo)
        return;

    player->energy -= carta.custo;

    // Move carta para o descarte
    player->baralhoDescarte.cartas[player->baralhoDescarte.quantity++] = carta;

    // Remove da mão
    for (int i = idx; i < player->qtdMaoCartas - 1; i++) {
        player->mao[i] = player->mao[i + 1];
    }

    player->qtdMaoCartas--;

    // Ajusta seleção para não ficar fora do limite
    if (player->selectedCarta >= player->qtdMaoCartas)
        player->selectedCarta = player->qtdMaoCartas - 1;

    // Garante que não fique negativo
    if (player->selectedCarta < 0)
        player->selectedCarta = 0;

    //Lógica de aplicação de cada carta
    if (carta.type == 'A') { //Carta de Ataque
        Inimigo *inimigoAlvo = &c->inimigos[player->selectedEnemy]; //Inimigo alvo escolhido
        aplicarDano(&inimigoAlvo->base, carta.effect);
        
        if(inimigoAlvo->base.life <= 0) {
            removerInimigo(c);
        }

        if(c->qtdInimigos == 0) {
            novoTurno(c);
        }
    }
    else if (carta.type == 'D') { // Carta de defesa
        aplicarEscudo(&player->base, carta.effect);
    }
    else { // Carta Especial
        aplicarEspecial(player);
    }
}

//Inicializa o jogo 
void startGame(Combate *combate){

    combate->turno = TURN_PLAYER;
    combate->qtdBatalhas = 0;
    combate->player = gerarPlayer();

    //Gera inimigos
    combate->qtdInimigos = 2;
    for (int i = 0; i < combate->qtdInimigos; i++) {
        gerarInimigo(&combate->inimigos[i]);
    }

    // Impede iniciar com 2 fortes
    while (combate->inimigos[0].type == 'F' && combate->inimigos[1].type == 'F') {
        gerarInimigo(&combate->inimigos[1]);
    }
    
    iniciarTurnoPlayer(&combate->player);
}


//Mata todos os inimigos da rodada e inicia novo turno
void killAllEnemies(Combate *combate) {
    for(int i = 0; i < combate->qtdInimigos; i++) {
        combate->inimigos[i].base.life = 0;
    }
    combate->qtdInimigos = 0;
    combate->player.selectedEnemy = 0;
    combate->player.selectedMode = 0;

    novoTurno(combate);
}


// PROCESSAMENTO DAS TECLAS DE SETA < e >
void ProcessSetaEsquerda(Combate *c)
{
    Player *player= &c->player;

    if (player->selectedMode == 0) {
        // navegando cartas
        if (player->selectedCarta > 0)
            player->selectedCarta--;
    }
    else {
        // escolhendo inimigo
        if (player->selectedEnemy > 0)
            player->selectedEnemy--;
    }
}

void ProcessSetaDireita(Combate *c)
{
    Player *player= &c->player;

    if (player->selectedMode == 0) {
        if (player->selectedCarta < player->qtdMaoCartas - 1)
            player->selectedCarta++;
    }
    else {
        if (player->selectedEnemy < c->qtdInimigos - 1)
            player->selectedEnemy++;
    }
}

void ProcessEsc(Combate *combate){
    Player *player = &combate->player;

    // Descartar toda a mão
    for (int i = 0; i < player->qtdMaoCartas; i++) {
        player->baralhoDescarte.cartas[player->baralhoDescarte.quantity++] = player->mao[i];
    }

    player->qtdMaoCartas = 0;

    // Agora turno passa para os inimigos
    combate->turno = TURN_ENEMIES;

    turnoInimigos(combate);
}

void ProcessEnter(Combate *c)
{
    Player *player= &c->player;

    if (c->turno != TURN_PLAYER)
        return; // só funciona no turno do jogador

    Carta carta = player->mao[player->selectedCarta];

    // Se está escolhendo inimigo, finaliza ataque
    if (player->selectedMode == 1) {

        jogarCarta(c); 
        player->selectedMode = 0;   
        return;
    }

    // cartas de ataque entram no modo de seleção se o custo energético for válido
    if (carta.type == 'A') {
        if(player->energy < carta.custo) {
            return;
        }
        player->selectedMode = 1;
        player->selectedEnemy = 0;
        return;
    }

    // defesa e especial resolvem direto
    jogarCarta(c);
}


