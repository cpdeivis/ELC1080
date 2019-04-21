#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/dir.h>

#include "Frase.h"

/* dicaDia
diretorio -> path da pasta a ser escrito o arquivo
head -> lista de frases
total -> total de frases */
void dicaDia(const char * diretorio, Frase * head, int * total){
    // PATH PARA O ARQUIVO
    char * arquivo;
    arquivo = malloc(sizeof(char) * (strlen(diretorio) + 16));
    strcpy(arquivo, diretorio);
    strcat(arquivo, "dica_do_dia.txt");
    // END PATH
    FILE * arq = fopen(arquivo, "w");//abre em modo escrita
    char * linha = sortFrase(head, total);//pega uma frase aleatória da lista
    fprintf(arq, "%s", linha);//escreve no arquivo
    fclose(arq);//fecha o arquivo
}

/* abrirRecursivamente
diretorio -> path da pasta a ser aberta
primeira -> flag da primeira chamada da função
head -> lista de frases
total -> total de frases */
void abrirRecursivamente(const char *diretorio, int primeira, Frase * head, int * total){
    DIR *dirp;
    dirp = opendir(diretorio);

    if(dirp != NULL){//verifica de o diretorio é válido, existe 
        struct dirent *dfilhos;
        char *new_dir;
        new_dir = malloc(sizeof(char) * (strlen(diretorio) + 256));

        dicaDia(diretorio, head, total);// função que cria a dica do dia

        if(!primeira)//execuções subsequentes
            printf("\t%d -> %d;\n", getppid(), getpid());

        printf("\t%d [label=\"%s, %d\"];\n", getpid(), diretorio, getpid());

        //enquanto tiver algo dentro do diretório atual
        while ((dfilhos = readdir(dirp)) != NULL){
            if (dfilhos->d_type & DT_DIR){//se for uma pasta, entra
                if (dfilhos->d_name[0] != '.'){//se não for do sistema
                    strcpy(new_dir, diretorio);      // MONTA O
                    strcat(new_dir, dfilhos->d_name);// CAMINHO DA
                    strcat(new_dir, "/");            // SUBPASTA

                    int pid = fork();//faz o fork pra essa subpasta
                    if (pid == 0){//execução do fork, FILHO
                        abrirRecursivamente(new_dir, 0, head, total);//abre o novo diretório
                        return; 
                    }
                }
            }
            wait(NULL);// execução PAI, espera seu FILHO terminar
        }
        closedir(dirp);//fecha o diretório atual

        if(primeira){
            puts("}");//para fazer a saída de forma correta
        }
    }
}

int main(int argc, char const *argv[]){
    int total = 0;
    //chama a função que carrega as frases para uma lista
    Frase *head = carregaFrases("./frases.txt", &total);
    if(total > 0){
        puts("digraph G {");
        abrirRecursivamente("./home/estagiario/", 1, head, &total);
    }

    return 0;
}
