#include <stdio.h>
#include <string.h>
#include "curl_code.h"


int seteCliques(const char *page_url, int *exe, const char *str){
	//verifica se não passou os limites de execução
	if(*exe < 8){
		printf("Link %d: %s \n", *exe, page_url);

		char *find;
		CURL *curl_handle;
		char *page_content = download_page(curl_handle, page_url);
		if(page_content == NULL)
			return 0;// deu PT

		find = strstr(page_content, str);
		if(find != NULL)
			return 1;// achou

		int links_readed;// links_readed: variavel onde o numero de links lidos eh salvo.
		// links: lista de links lidos. A funcao find_links ira tentar ler 50
		// links dentro da pagina.
		char **links = find_links(curl_handle, page_content, 50, &links_readed);
		if(links_readed > 0){
			int random = rand() % links_readed;//sorteia um link da página
			*exe += 1;//incrementa o contador das páginas
			return seteCliques(links[random], exe, str);
		}
	}
	else
		return 0;
}

int main(int argc, char const *argv[]){
	//arg 1: Página Inicial
    //arg 2: Palavra a ser Encontrada
	if(argc == 3){
		srand(time(NULL));
		int exe = 0;
		if(seteCliques(argv[1], &exe, argv[2])){
			puts("Achou!!");
		} else{
			puts("Não foi Encontrado!!");
		}

		curl_global_cleanup();
	} else{
        puts("Argumentos Insuficientes!!");
    }
	return 0;
}