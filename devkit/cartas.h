#ifndef CARTAS_H
#define CARTAS_H

typedef struct {
    char type;   // A = ataque, D = defesa, S = especial
    int custo;   // 0 a 3
    int effect;  // depende do custo
} Carta;

typedef struct {
    int quantity;
    Carta cartas[20];
} Baralho;

int gerarEfeito(char type, int custo);
void criarCartasObrigatorias(Carta *c, int *idx, char typeCarta, int cust0, int cust1, int cust2, int cust3);
void criarCartasAleatorias(Carta *c, int *idx, char typeCarta, int qtd, int intervaloSup);
void createBaralho(Baralho *b);
void embaralharBaralho(Baralho *b);

#endif
