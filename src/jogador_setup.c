#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cartas.h" 

typedef struct {
    int life;
    Baralho baralho;
}Player;


int main(void) {
    srand(time(NULL)); 
    Player player;
    Baralho baralho;
    player.life = 100;

    createBaralho(&baralho);

    for (int i = 0; i < 20; i++) {
        printf("Carta %d%c: custo %d efeito: %d\n", i, baralho.cartas[i].type, baralho.cartas[i].custo, baralho.cartas[i].effect);
    }
    /* printf("Quantidade de vida do player: %d\n", player.life);
    printf("Quantidade de cartas do baralho do player: %d\n", player.baralho.quantity); */
    
    return 0;
}