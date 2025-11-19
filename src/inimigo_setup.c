#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int life;
    char type;
    char *cicloJogada;
}Inimigo;

void setAcaoInimigo(Inimigo *inimigo) {
    if(inimigo.type == 'A') {
        for(int i = 0;)
    } else {

    }
}

void gerarInimigo(Inimigo *inimigo) {
    int number = (rand() % 20);
    int qtdAcoes;

    if (number == 0) {
        printf("Foi gerado um inimigo forte!!!!! %d\n", number);
        inimigo->life = 40 + (rand() % (100 - 40) + 1);
        inimigo->type = 'A';

        qtdAcoes = 1 + (rand() % (2 - 1 + 1));
        char *v = malloc(qtdAcoes * sizeof(char)); 
    } else {
        printf("Foi gerado um inimigo fraco:: %d\n", number);
        inimigo->life = 10 + (rand() % (30-10) + 1);
        inimigo->type = 'C
        ';
        qtdAcoes = 2 + (rand() % (3 - 2 + 1));
        char *v = malloc(qtdAcoes * sizeof(char));

    }
}

int main() {
    srand(time(NULL));

    Inimigo inimigo1;

    gerarInimigo(&inimigo1);

    printf("Vida do inimigo gerado: %d\n", inimigo1.life);
    return 1;
}