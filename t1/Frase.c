#include <stdio.h>
#include <stdlib.h>

#include "Frase.h"

/* getLine
arq -> estrutura do tipo FILE
bEOF -> flag para o fim do arquivo
nrChars -> contador de chars lidos naquela linha */
char * getLine(FILE *arq, int *bEOF, size_t *nrChars){
    char * line; //buffer da string
    char ch; //para leitura caracter a caracter
    size_t len = 0; //numero de carateres lidos
    size_t lineSize = 128; //tamanho padrão de 128 
    *nrChars = 0;

    if(!arq) //só verifica se o arquivo está ok
        return NULL;
    //alocação do buffer
    line = malloc(sizeof(char)*lineSize);

    if(!line) //só verifica se a alocação foi ok
        return NULL;
    
    while(1){ //bad practice rsrs
        ch = fgetc(arq);
        if(ch == '\n') 
            break;//se chegou ao fim da linha, para o loop
        if(ch == EOF){
            *bEOF = 1;
            break;//se chegou ao fim do arquivo, para o loop
        }

        line[len] = ch;//armazena o caracter no buffer
        len++;//aumenta o contador de tamanho
        if(len == lineSize){ // estourou o tamanho do buffer e não acabou a linha
            lineSize += 64;
            line = realloc(line, sizeof(char)*lineSize);
            if(!line)
                return NULL;
        }
    }
    if(len == 0 && *bEOF)
        return NULL; //arquivo vazio
    
    line[len++] ='\0';
    line = realloc(line, sizeof(char)*len); //ajusta para o real tamanho usado
    *nrChars = len;

    return line;
}

Frase * carregaFrases(const char * arquivo, int * total){
    FILE *dicas; // arquivo das frases
    dicas = fopen(arquivo, "r"); 
    if(dicas != NULL){// verifica se abriu o arquivo corretamente
        char * line;//buffer pra linha
        int bEOF = 0;//flag para o EOF
        size_t nrChars = 0;//contador de chars lidos
        Frase *atual, *head;//lista das frases
        atual = head = NULL; 
        *total = 0;//contador de elementos
        while(line = getLine(dicas, &bEOF, &nrChars)){//alimenta o buffer
            if((nrChars == 0) && bEOF) break; // arquivo vazio
            if(nrChars == 1) continue;// linha vazia
            Frase *f = malloc(sizeof(Frase));//cria uma nova entrada na lista
            f->texto = line;//passa o conteudo do buffer
            f->prox =  NULL;

            *total += 1;//contador de elementos

            if(head == NULL){
                atual = head = f;//primeiro elemento
            } else{
                atual = atual->prox = f;//subsequentes
            }

            if(bEOF) break;// fim do arquivo
        }
        if(dicas)
            fclose(dicas);//se abriu o arquivo, fecha-o
        
        return head;
    }
    return NULL;
}

char * sortFrase(Frase * head, int * total){
    if(head != NULL && *total > 0){
        Frase * atual = head;
        for (int i = 0, tt = (rand() % *total); i < tt; i++){
            atual = atual->prox;
        }
        return atual->texto;
    }
    return NULL;
}