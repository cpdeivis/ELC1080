#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "curl_code.h"

typedef struct{
    int thread;
    int execs;
    const char * page_url;
    const char * find_str;
} argumentos;

void *seteCliques(void * args){
    argumentos * atual = args;
    char *find;
	CURL *curl_handle;
	char *page_content;
    int links_readed = 0;// links_readed: variavel onde o numero de links lidos eh salvo.
    char **links;// links dentro da pagina.
    int random;
    while(atual->execs < 8){
        printf("T%d Link %d: %s \n", atual->thread, atual->execs, atual->page_url);
        page_content = download_page(curl_handle, atual->page_url);
        if(page_content == NULL){
			break;// deu PT
        }
        find = strstr(page_content, atual->find_str);
		if(find != NULL){
            printf("T%d: Achou!!\n", atual->thread);
            free(atual);
            exit(0);// achou
        }
        // links: lista de links lidos. A funcao find_links ira tentar ler 50
        links = find_links(curl_handle, page_content, 50, &links_readed);
        if(links_readed > 0){
            random = rand() % links_readed;
			atual->execs += 1;//incrementa o contador das páginas
            atual->page_url = links[random];
        } else{
            break;
        } 
    }
    printf("T%d: Não foi Encontrado!!\n", atual->thread);
    free(atual);
}

int main(int argc, char const *argv[]){
    //arg 1: Página Inicial
    //arg 2: Palavra a ser Encontrada
    //arg 3: Número de Threads
    if(argc == 4){
        int nThreads = atoi(argv[3]);
        if(nThreads > 0){
            srand(time(NULL));
            pthread_t arrayT[nThreads];
            for(int i = 0; i < nThreads; i++){
                argumentos *args = malloc(sizeof *args);
                args->find_str = argv[2];
                args->page_url = argv[1];
                args->thread = i;
                args->execs = 0;

                pthread_create(&arrayT[i], NULL, seteCliques, args);
            }
            for(int i = 0; i < nThreads; i++){
                pthread_join(arrayT[i], NULL);
            }

            curl_global_cleanup();
        } else{
            puts("Número de Threads Inválido!!");
        }
    } else{
        puts("Argumentos Insuficientes!!");
    }
    return 0;
}
