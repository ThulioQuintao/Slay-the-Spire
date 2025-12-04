#ifndef INIMIGO_H
#define INIMIGO_H

#include "entidade.h"
#include "jogador.h"

typedef struct {
    char type;
    int effect;
    int custo;
} Acao;

typedef struct {
    Entidade base;
    char type;
    int qtdAcoes;
    Acao *cicloJogada;
    int indiceAcaoAtual;
} Inimigo;

void setAcaoInimigo(Inimigo *inimigo);
void gerarInimigo(Inimigo *inimigo);
void executarAcao(Inimigo *inimigo, Player *player);
#endif
