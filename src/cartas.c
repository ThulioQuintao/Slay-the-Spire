
#include <stdio.h>
#include <stdlib.h>
#include "cartas.h"  

void gerarEfeito(Carta *c) {
    if(c->type != 'E') {
        if(c->custo == 0) {
            c->effect = 1 + (rand() % (5 - 1 + 1));
        } else if (c->custo == 1) {
            c->effect = 5 + (rand() % (10 - 5 + 1));
        } else if (c->custo == 2){
            c->effect = 10 + (rand() % (15 - 10 + 1));
        } else {
            c->effect = 15 + (rand() % (30 - 15 + 1));
        }
    } else {
        c->effect = 0;
    }
}

void criarCartasObrigatorias(Carta *c, int *idx, char typeCarta, int cust0, int cust1, int cust2, int cust3) {
    for(int i = 0; i < cust0; i++) {
        c[*idx].custo = 0;
        c[*idx].type = typeCarta;
        gerarEfeito(&c[*idx]);
        (*idx)++;
    }

    for(int i = 0; i < cust1; i++) {
        c[*idx].custo = 1;
        c[*idx].type = typeCarta;
        gerarEfeito(&c[*idx]);
        (*idx)++;
    } 

    for(int i = 0; i < cust2; i++) {
        c[*idx].custo = 2;
        c[*idx].type = typeCarta;
        gerarEfeito(&c[*idx]);
        (*idx)++;
    }

    for(int i = 0; i < cust3; i++) {
        c[*idx].custo = 3;
        c[*idx].type = typeCarta;
        gerarEfeito(&c[*idx]);
        (*idx)++;
    }
}

void criarCartasAleatorias(Carta *c, int *idx, char typeCarta, int qtd, int intervaloSup){
    for(int i = 0; i < qtd; i++) {
        c[*idx].custo = rand() % intervaloSup;
        c[*idx].type = typeCarta;
        gerarEfeito(&c[*idx]);
        (*idx)++;
    }
}

void createBaralho(Baralho *b) {
    int idx = 0;
    
    criarCartasObrigatorias(b -> cartas, &idx, 'A', 1, 3, 1, 1); // 6 cartas de ataque obrigatórias
    criarCartasAleatorias(b -> cartas, &idx, 'A', 4, 4); // 4 cartas aleatórias de ataque

    criarCartasObrigatorias(b -> cartas, &idx, 'D', 1, 3, 1, 1); // 6 cartas de defesa obrigatórias
    criarCartasAleatorias(b -> cartas, &idx, 'D', 2, 3); // 2 cartas aleatórias de defesa

    criarCartasObrigatorias(b -> cartas, &idx, 'E', 2, 0, 0, 0); // 2 cartas especiais obrigatórias
}
