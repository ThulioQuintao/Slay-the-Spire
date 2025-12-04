#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jogador.h"
#include "combate.h"

void comprarCarta(Player *p)
{
    // Vamos comprar sempre 5 cartas
    int qtdComprar = 5;

    for (int i = 0; i < qtdComprar; i++)
    {
        // Se a pilha de compra está vazia → recicla descarte
        if (p->baralhoCompra.quantity == 0){
            // mover descarte → compra
            for (int k = 0; k < p->baralhoDescarte.quantity; k++){
                p->baralhoCompra.cartas[k] = p->baralhoDescarte.cartas[k];
            }

            p->baralhoCompra.quantity = p->baralhoDescarte.quantity;
            p->baralhoDescarte.quantity = 0;

            // embaralhar
            embaralharBaralho(&p->baralhoCompra);
        }

        // Compra 1 cart
        p->mao[p->qtdMaoCartas] = p->baralhoCompra.cartas[p->baralhoCompra.quantity - 1];

        p->qtdMaoCartas++;
        p->baralhoCompra.quantity--;
    }
}

void iniciarTurnoPlayer(Player *player) {
    player->base.shield = 0;
    player->energy = 3;
    player->qtdMaoCartas = 0;

    comprarCarta(player);
}

void aplicarEspecial(Player *player) {
    for (int i = 0; i < player->qtdMaoCartas; i++) {
        player->baralhoDescarte.cartas[player->baralhoDescarte.quantity++] = player->mao[i];
    }

    player->qtdMaoCartas = 0;

    comprarCarta(player);
}

Player gerarPlayer() {
    Player p;

    p.base.life = 100;
    p.base.maxLife = 100;
    p.base.shield = 0;

    createBaralho(&p.baralhoCompra);
    p.baralhoDescarte.quantity = 0;

    p.qtdMaoCartas = 0;
    p.selectedCarta = 0;
    p.selectedEnemy = 0;
    p.selectedMode = 0;


    return p;
}
