#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/dir.h>

void dicaDia(const char * diretorio){
    // TODO
}

void abrirRecursivamente(const char *diretorio, int primeira){
    DIR *dirp;
    dirp = opendir(diretorio);

    if(dirp != NULL){
        struct dirent *dfilhos;
        char *new_dir;
        new_dir = malloc(sizeof(char) * (strlen(diretorio) + 256));

        dicaDia(diretorio);

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
                        abrirRecursivamente(new_dir, 0);
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
    puts("digraph G {");
    abrirRecursivamente("./home/estagiario/", 1);
    return 0;
}
