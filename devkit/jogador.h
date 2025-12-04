#ifndef JOGADOR_H
#define JOGADOR_H

#include "entidade.h"
#include "cartas.h"

typedef struct {
    Entidade base;
    int energy;

    Baralho baralhoCompra;
    Baralho baralhoDescarte;

    Carta mao[5];
    int qtdMaoCartas;

    int selectedCarta;
    int selectedEnemy;
    int selectedMode;
} Player;

void comprarCarta(Player *p);
void iniciarTurnoPlayer(Player *p);
void aplicarEspecial(Player *p);
Player gerarPlayer();

#endif
