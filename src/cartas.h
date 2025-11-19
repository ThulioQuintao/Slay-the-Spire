typedef struct {
    char type;
    int custo;
    int effect;
}Carta;

typedef struct {
    int quantity;
    Carta cartas[50];
}Baralho;


void gerarEfeito(Carta *c);
void criarCartasObrigatorias(Carta *c, int *idx, char typeCarta, int cust0, int cust1, int cust2, int cust3);
void criarCartasAleatorias(Carta *c, int *idx, char typeCarta, int qtd, int intervaloSup);
void createBaralho(Baralho *b);