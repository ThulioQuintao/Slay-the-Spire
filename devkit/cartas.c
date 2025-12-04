#include <stdio.h>
#include <stdlib.h>
#include "cartas.h"
    

int gerarEfeito(char type, int custo) {

    if (type == 'E') { // se for especial, efeito 0 e custo 0 (já implementado)
        return 0; 
    }

    const int min[] = {1, 5, 10, 15};
    const int range[] = {5, 6, 6, 16};

    return min[custo] + rand() % range[custo]; // consulta o intervalo pelo índice do custo
}


void createCarta(Carta *carta, int idx, char typeCarta, int custo) {
    carta[idx].custo = custo;
    carta[idx].type = typeCarta;
    carta[idx].effect = gerarEfeito(carta[idx].type, carta[idx].custo);
}

void createCartasObrigatorias(Carta *carta, int *idx, char typeCarta, int cust0, int cust1, int cust2, int cust3) {
    for (int i = 0; i < cust0; i++) {
        createCarta(carta, *idx, typeCarta, 0);
        (*idx)++;
    }

    for (int i = 0; i < cust1; i++) {
        createCarta(carta, *idx, typeCarta, 1);
        (*idx)++;
    }

    for (int i = 0; i < cust2; i++) {
        createCarta(carta, *idx, typeCarta, 2);
        (*idx)++;
    }

    for (int i = 0; i < cust3; i++) {
        createCarta(carta, *idx, typeCarta, 3);
        (*idx)++;
    }
}

void createCartasAleatorias(Carta *c, int *idx, char typeCarta, int qtd, int intervaloSup){
    for(int i = 0; i < qtd; i++) {
        c[*idx].custo = rand() % intervaloSup;
        c[*idx].type = typeCarta;
        c[*idx].effect = gerarEfeito(c[*idx].type, c[*idx].custo);
        (*idx)++;
    }
}

void embaralharBaralho(Baralho *baralho) {
    for (int i = 0; i < baralho->quantity - 1; i++) {
        int j = i + rand() % (baralho->quantity - i);

        Carta temp = baralho->cartas[i];
        baralho->cartas[i] = baralho->cartas[j];
        baralho->cartas[j] = temp;
    }
}

void createBaralho(Baralho *baralho) {
    int idx = 0;
    
    createCartasObrigatorias(baralho -> cartas, &idx, 'A', 1, 3, 1, 1); // 6 cartas de ataque obrigatórias
    createCartasAleatorias(baralho -> cartas, &idx, 'A', 4, 4); // 4 cartas aleatórias de ataque

    createCartasObrigatorias(baralho -> cartas, &idx, 'D', 1, 3, 1, 1); // 6 cartas de defesa obrigatórias
    createCartasAleatorias(baralho -> cartas, &idx, 'D', 2, 3); // 2 cartas aleatórias de defesa

    createCartasObrigatorias(baralho -> cartas, &idx, 'E', 2, 0, 0, 0); // 2 cartas especiais obrigatórias

    //DELETAR
        
    //
    baralho->quantity = idx; 

    embaralharBaralho(baralho);
}

