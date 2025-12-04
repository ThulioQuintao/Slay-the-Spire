#include <stdio.h>
#include <stdlib.h>
#include "inimigo.h"
#include "cartas.h"

//Seta a ação da IA do inimigo de acordo com sua classe (f ou F)
void setAcaoInimigo(Inimigo *inimigo) {

    if (inimigo->type == 'f') { //inimigo fraco

        for (int i = 0; i < inimigo->qtdAcoes; i++) {

            int tipoAcao = rand() % 2;
            int custo = rand() % 2;

            inimigo->cicloJogada[i].type = tipoAcao ? 'A' : 'D';
            inimigo->cicloJogada[i].custo = custo;
            inimigo->cicloJogada[i].effect = gerarEfeito('A', custo);
            
        }

    } else { //inimigo forte

        int usouCusto1 = 0;

        for (int i = 0; i < inimigo->qtdAcoes; i++) {

            int tipoAcao = rand() % 2;
            int custo;

            if (!usouCusto1) {
                custo = 1 + rand() % 3;
                if (custo == 1) usouCusto1 = 1;
            } else {
                custo = 2 + rand() % 2;
            }

            inimigo->cicloJogada[i].type = tipoAcao ? 'A' : 'D';
            inimigo->cicloJogada[i].custo = custo;
            char tipo = inimigo->cicloJogada[i].type;
            inimigo->cicloJogada[i].effect = gerarEfeito(tipo, custo);
      
        }
    }

    //Se o inimigo gerado não tiver ataque, será sorteado um ataque em suas ações
    int temAtaque = 0;
    for (int i = 0; i < inimigo->qtdAcoes; i++) {
        if (inimigo->cicloJogada[i].type == 'A') {
            temAtaque = 1;
            break;
        }
    }

    if (!temAtaque) {
        int pos = rand() % inimigo->qtdAcoes;
        inimigo->cicloJogada[pos].type = 'A';
        inimigo->cicloJogada[pos].effect =
            gerarEfeito('A', inimigo->cicloJogada[pos].custo);
    }
}

//gera um inimigo aleatório
void gerarInimigo(Inimigo *inimigo) {
    int number = rand() % 20;

    inimigo->indiceAcaoAtual = 0;

    if (number == 0) {
        inimigo->type = 'F';
        inimigo->base.life = 40 + rand() % 61;
        inimigo->qtdAcoes = 2 + rand() % 2;
        
    } else {
        inimigo->type = 'f';
        inimigo->base.life = 10 + rand() % 21;
        inimigo->qtdAcoes = 1 + rand() % 2;
        
    }

    inimigo->base.maxLife = inimigo->base.life;
    inimigo->base.shield = 0;

   
    inimigo->cicloJogada = malloc(inimigo->qtdAcoes * sizeof(Acao));

    setAcaoInimigo(inimigo);
    
}

void executarAcao(Inimigo *inimigo, Player *player) {
    Acao *acaoInimigo = &inimigo->cicloJogada[inimigo->indiceAcaoAtual];

    if (acaoInimigo->type == 'A') {
        aplicarDano(&player->base, acaoInimigo->effect);
        printf("Dano aplicado: %d", acaoInimigo->effect);
    }
    else if (acaoInimigo->type == 'D') {
        aplicarEscudo(&inimigo->base, acaoInimigo->effect);
    }

    // avança ciclo da IA do inimigo para próxima ação
    inimigo->indiceAcaoAtual++;
    if (inimigo->indiceAcaoAtual >= inimigo->qtdAcoes)
        inimigo->indiceAcaoAtual = 0;
}

