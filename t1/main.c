#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <string.h>

void abrirRecursivamente(const char * diretorio){
    DIR *dirp;
    struct dirent *dp;
    dirp = opendir(diretorio);
    char * new_dir;
    new_dir = malloc(sizeof(char) * (strlen(diretorio) + 256));
    while ((dp = readdir(dirp)) != NULL){
        if (dp->d_type & DT_DIR){
            if (dp->d_name[0] != '.'){
                strcpy(new_dir, diretorio);
                strcat(new_dir, dp->d_name);
                strcat(new_dir, "/");
                puts(new_dir);
                abrirRecursivamente(new_dir);
            }
        }
    }
    closedir(dirp);
}

int main(int argc, char const *argv[]){
    
    abrirRecursivamente("/home/cpdeivis/playground/");
    return 0;
}
