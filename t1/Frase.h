struct Frase{
    char * texto;
    struct Frase * prox;
} typedef Frase;

/* carregaFrases
arquivo -> caminho para acessar o mesmo
total -> contador de linhas/frases lidas */
Frase * carregaFrases(const char * arquivo, int * total);
/* sortFrase
head -> lista de frases
total -> total de frases */
char * sortFrase(Frase * head, int * total);