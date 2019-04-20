#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Frase.h"

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
    FILE *dicas;
    dicas = fopen(arquivo, "r");
    if(dicas != NULL){
        char * line;
        int bEOF = 0;
        size_t nrChars = 0;
        Frase *atual, *head;
        atual = head = NULL; 
        *total = 0;
        while(line = getLine(dicas, &bEOF, &nrChars)){
            if((nrChars == 0) && bEOF) break; // arquivo vazio
            if(nrChars == 1) continue;// linha vazia
            Frase *f = malloc(sizeof(Frase));
            f->texto = line;
            f->prox =  NULL;

            *total += 1;

            if(head == NULL){
                atual = head = f;
            } else{
                atual = atual->prox = f;
            }

            if(bEOF) break;// fim do arquivo
        }
        if(dicas)
            fclose(dicas);
        
        return head;
    }
    return NULL;
}

char * sortFrase(Frase * head, int * total){
    if(head != NULL && *total > 0){
        srand(time(NULL));
        Frase * atual = head;
        for (int i = 0, tt = (rand() % *total); i < tt; i++){
            atual = atual->prox;
        }
        return atual->texto;
    }
    return NULL;
}