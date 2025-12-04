#ifndef ENTIDADE_H
#define ENTIDADE_H

typedef struct {
    int life;
    int maxLife;
    int shield;
} Entidade;

void aplicarDano(Entidade *alvo, int dano);
void aplicarEscudo(Entidade *alvo, int shield);

#endif