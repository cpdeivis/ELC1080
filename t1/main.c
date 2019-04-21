#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/dir.h>

#include "Frase.h"

void dicaDia(const char * diretorio, Frase * head, int * total){
    char * arquivo;
    arquivo = malloc(sizeof(char) * (strlen(diretorio) + 16));
    strcpy(arquivo, diretorio);
    strcat(arquivo, "dica_do_dia.txt");
    FILE * arq = fopen(arquivo, "w");
    char * linha = sortFrase(head, total);
    fprintf(arq, "%s", linha);
    fclose(arq);
}

void abrirRecursivamente(const char *diretorio, int primeira, Frase * head, int * total){
    DIR *dirp;
    dirp = opendir(diretorio);

    if(dirp != NULL){
        struct dirent *dfilhos;
        char *new_dir;
        new_dir = malloc(sizeof(char) * (strlen(diretorio) + 256));

        dicaDia(diretorio, head, total);

        if(!primeira)
            printf("\t%d -> %d;\n", getppid(), getpid());

        printf("\t%d [label=\"%s, %d\"];\n", getpid(), diretorio, getpid());

        while ((dfilhos = readdir(dirp)) != NULL){
            if (dfilhos->d_type & DT_DIR){
                if (dfilhos->d_name[0] != '.'){
                    strcpy(new_dir, diretorio);
                    strcat(new_dir, dfilhos->d_name);
                    strcat(new_dir, "/");

                    int pid = fork();
                    if (pid == 0){
                        abrirRecursivamente(new_dir, 0, head, total);
                        return; 
                    }
                }
            }
            wait(NULL); 
        }
        closedir(dirp);

        if(primeira){
            puts("}");    
        }
    }
}

int main(int argc, char const *argv[]){
    int total = 0;
    Frase *head = carregaFrases("./frases.txt", &total);
    if(total > 0){
        puts("digraph G {");
        abrirRecursivamente("./home/estagiario/", 1, head, &total);
    }

    return 0;
}
