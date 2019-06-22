#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

// 3. A sala do DCE, onde os alunos entram para entregar os 
//    documentos, possui uma lotação máxima de 5 lugares
#define N 5

typedef struct{
    int estudante;
    int ficha;
} ficha;

int total;//qts estudantes já foram processados
int ind;//indice atual da queue
int num;//total de estudantes, passado por parametro
int queue[N];//ordem de quem usou o MUTEX

sem_t fichas[N];
sem_t mutex;

void * Estudante(void * args){
    ficha * atual = args;
    sem_wait(&fichas[atual->ficha]);

    printf("Ficha %d: Entrei. Trouxe meus documentos.\n", atual->estudante);
    printf("Ficha %d: Vou esperar pela minha carteirinha...\n", atual->estudante);
    total++;
    queue[ind++] = atual->estudante;
    sem_wait(&mutex);
    printf("Ficha %d: Recebi minha carteirinha!\n\n", atual->estudante);
}

void * Bolsista(void * esquece){
    while(1){
        if(total % N == 0){
            printf("Bolsista: Voltei. Vou trabalhar...\n");
            for(int i = 0; i < N; i++){
                printf("Bolsista: Verificando os documentos da ficha %d.\n", queue[i]);
                printf("Bolsista: Tudo certo com os documentos. Entregando a carteirinha da ficha %d.\n", queue[i]);
                sem_post(&mutex);
                sleep(1);
            }

            printf("Bolsista: Terminei. Fechei a porta. Vou tomar um cafezinho e jah volto...\n");
            ind = 0;
            for(int i = 0; i < N; i++){
                sem_post(&fichas[i]);
            }
        }
        if(total == num)
            break;
        sleep(1);
    }
}

// 5. O número de fichas deve ser passado como parâmetro 
//    por linha de comando ao programa
int main(int argc, char const *argv[]){
    //Verifica se a entrada está correta
    if (argc == 2 && argv[1] > 0){
        num = atoi(argv[1]);
    } else{ 
        printf("Numero Inválido!\n");
    }

    // inicializa o vetor de semaforos
    for(int i = 0; i < N; i++)
        sem_init(&fichas[i], 0, 1);

    total = 0;
    ind = 0;

    // 1. Os alunos são implementados através de fichas, onde cada ficha é
    //    uma thread que roda indefinidamente fazendo as suas ações
    pthread_t alunos[num];
    for (int i = 0; i < num; i++){
        ficha *args = malloc(sizeof *args);
        args->estudante = i;
        args->ficha = i%N;

        pthread_create(&alunos[i], NULL, (void*) Estudante, args);
    }
    pthread_t bolsista;
    pthread_create(&bolsista, NULL, (void*) Bolsista, NULL);

    pthread_join(bolsista, NULL);
    for(int i = 0; i < num; i++)
        pthread_join(alunos[i], NULL);

    return 0;
}