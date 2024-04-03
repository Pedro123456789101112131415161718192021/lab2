#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
    int id, comeco, rep;
    float *vetor;
    float *soma;
} argT;


void somaVetor(void *arg){
    argT *args = (argT *) arg;
    for(int i = args->comeco; i < args->comeco + args->rep; i++){
        args->soma[args->id] += args->vetor[i];
    }
}


int main(int argc, char *argv[]){
    int nthread, tamv, tams;

    if(argc < 2){
        printf("Defina o numero de threads");
        return 1;
    }

    nthread=atol(argv[1]);
    if(nthread < 1){
        printf("O numero de threads deve ser no minimo 1");
        return 2;
    }

    scanf("%d", &tamv);//armazena o tamanho do vetor

    float *vetor = (float*)malloc(tamv * sizeof(float)); //aloca memoria para o vetor principal

    tams = nthread;

    float *soma = (float*)calloc(tams, sizeof(float)); //aloca memoria para o vetor das somas

    for(int i = 0; i < tamv; i++){
        scanf("%f", &vetor[i]);
    }

    pthread_t tid_sistema[nthread];
    argT arg[nthread];

    for(int i = 0; i < nthread; i++){
        arg[i].id = i;
        arg[i].rep = tamv/nthread;
        arg[i].comeco = arg[i].id * arg[i].rep;
        arg[i].vetor = vetor;
        arg[i].soma = soma;
        if(pthread_create(&tid_sistema[i], NULL, somaVetor, (void*) &arg[i])){
            printf("ERRO");
            exit(-1);
        }
    }

    for (int i=0; i<nthread; i++) {
        if (pthread_join(tid_sistema[i], NULL)) {
            printf("--ERRO: pthread_join() \n");
            exit(-1);
        }
    }

    if(tamv % nthread != 0){
        for(int i = tamv/nthread*nthread; i < tamv; i++){
            soma[0] += vetor[i];
        }
    }

    float somat = 0;
    for(int i = 0; i < tams; i++){
        somat += soma[i];
    }


    printf("Soma total = %f", somat);

    free(vetor);
    free(soma);

}
