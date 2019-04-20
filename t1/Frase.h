struct Frase{
    char * texto;
    struct Frase * prox;
} typedef Frase;

Frase * carregaFrases(const char * arquivo, int * total);
char * sortFrase(Frase * head, int * total);