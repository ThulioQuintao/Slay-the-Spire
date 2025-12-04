#include "entidade.h"

void aplicarDano(Entidade *alvo, int dano) {
    if(alvo->shield > 0) {
        int reducao = (dano <= alvo->shield) ? dano : alvo->shield;

        alvo->shield -= reducao;
        dano -= reducao;
    }

    if(dano > 0) {
        alvo->life -= dano;
    }
}

void aplicarEscudo(Entidade *alvo, int shield) {
    alvo->shield += shield;
}