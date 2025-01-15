#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "pImg.h" //o programa toma as declarações implícitas de io_pbm.h
#include "decode.h"


#define WIDTH 209
#define HEIGHT 58


int cabeca_pbm(FILE *file, int *width, int *height){
    char format[3];
    if(fscanf(file, "%2s", format)!=1 || strcmp(format, "P1")!=0){
        fprintf(stderr, "ERRO: não é um arquivo PBM válido\n");
        return -1; 
    }//leitura da formatação: checa se o formato P1 esta indicado


    if(fscanf(file, "%d %d", width, height)!=2){
        fprintf(stderr, "ERRO: falha na leitura das dimensões da imagem\n");
        return -1;
    }//leitura de dimensões
    
    return 0;
}


unsigned char** dados_pbm(FILE *file, int width, int height){
    unsigned char **image = (unsigned char **)malloc(height *sizeof(unsigned char *));
    //cria espaço na memória para altura da imagem fornecida 
    if(image==NULL){
        fprintf(stderr, "ERRO: falha na alocação de memória\n");
        return NULL;
    }

    for (int i=0; i<height;i++){
        image[i]=(unsigned char *)malloc(width * sizeof(unsigned char));
        if (image[i]==NULL){
            fprintf(stderr, "ERRO: falha de alocação da memória nas linhas da imagem\n");
            return NULL;
        }
    }

    for (int i=0; i<height;i++){
        for(int j=0;j<width;j++){
            if((fscanf(file,"%hhu", &image[i][j])!=1)){ //alterar comparação de ponteiro
                fprintf(stderr,"ERRO: falha em ler dados de imagem\n");
                return NULL;
            }
        }
    }


    return image;

}

void libera_pbm(int **dadosImg, int height){
    for(int i=0;i<height;i++){
        free(dadosImg[i]);
    }    
    free(dadosImg);
}//libera a alocação com o ponteiro

int main(int argc, char*argv[]){ 
    int image_d[HEIGHT][WIDTH];
    //alocação dinâmmica para dados da imagem
    int **image_dnm=(int **)malloc(HEIGHT * sizeof(int *));
    //precisamos da alocação para cada número dado na altura
    //image_dnm: array 2D alocado dinamicamente
    for (int i=0;i<HEIGHT;i++){
        image_dnm[i]=(int *)malloc(WIDTH *sizeof(int));
    }

    carrega_pbm(argv[1], image_d);
    
    int image[HEIGHT][WIDTH] = {0};
    int status;
    int x, y, larg, alt;
    int width, height;
    int bin_representa[56]={0}, decode_d[8]={0};
    
    if(argc!=2){
        fprintf(stderr, "Usage: %s <pbm_file>\n", argv[0]);
        return 1;
    }
    //arquivo é aberto
    FILE *arquivo=fopen(argv[1], "r");
        //ocorre a leitura
    if(arquivo==NULL){
        fprintf(stderr, "ERRO: falha em abrir o arquivo %s\n", argv[1]);
        return 1;
    }
    

    fclose(arquivo);

    //argv[1] guarda o nome do arquivo em .pbm
    verbarra_pbm(image, &x, &y, &larg, &alt);
    decode_ean8(bin_representa, decode_d, &status);
    checasoma(decode_d);


    
    int checaSoma=checasoma(decode_d);



    if(status!=0 && checaSoma!=0){
        printf("Código EAN-8\n");
        for (int k=0; k<8;k++){
            printf("%d ", decode_d[k]);
        }
        printf("\n");
    }

    int dadosImg[HEIGHT][WIDTH];
    //copia os elementos da imagem para a variável
    for(int i=0;i<HEIGHT;i++){
        for (int j=0;j<WIDTH;j++){
            dadosImg[i][j]=image[i][j];
        }
    }
    
    libera_pbm(image_dnm,height);
    //libera para image

    return 0;
}

