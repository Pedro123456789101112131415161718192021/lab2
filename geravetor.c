#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define max 3300

int main(int argc, char *argv[]){
    int nel, fator;
    double elem, soma;


    if(argc < 2){
        printf("Defina o numero de elementos");
        return 1;
    }

    nel=atol(argv[1]);
    if(nel < 1){
        printf("O numero de elementos deve ser no minimo 1");
        return 2;
    }

    srand((unsigned)time(NULL));

    printf("%d\n", nel);

    for(int i = 0; i < nel; i++){
        elem = (rand() % max) / 3.3;
        fator = rand();
        if((fator%2) == 0){
            fator = 1;
        }
        else{
            fator = -1;
        }
        elem *= fator;
        soma += elem;
        printf("%f ", elem);
    }

    printf("\n%f", soma);

    return 0;

}
