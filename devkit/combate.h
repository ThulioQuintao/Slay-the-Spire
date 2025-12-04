#ifndef COMBATE_H
#define COMBATE_H

#include "jogador.h"
#include "inimigo.h"
#include "entidade.h"

typedef struct {
    Player player;
    Inimigo inimigos[2];
    int qtdInimigos;
    int qtdBatalhas;     
    int turno;            
} Combate;


// controle básico de teclado
void startGame(Combate *combate);
void ProcessEnter(Combate *c);
void ProcessSetaEsquerda(Combate *c);
void ProcessSetaDireita(Combate *c);
void ProcessEsc(Combate *c);  
void jogarCarta(Combate *c);
void turnoInimigos(Combate *c);
void killAllEnemies(Combate *combate);

#endif
