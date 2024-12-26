#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "decode.h"
#include "io_pbm.h"
#define WIDTH 209 //colocar esse números no arquivo h
#define HEIGHT 58

const int start_end_pattern[] = {1, 0, 1};
const int f_end_pattern[] = {1, 0, 1};
const int c_end_pattern[] = {0, 1, 0, 1, 0};
const int left_digit_patterns[10][7] = {
    {0, 0, 0, 1, 1, 0, 1},
    {0, 0, 1, 1, 0, 0, 1},
    {0, 0, 1, 0, 0, 1, 1},
    {0, 1, 1, 1, 1, 0, 1},
    {0, 1, 0, 0, 0, 1, 1},
    {0, 1, 1, 0, 0, 0, 1},
    {0, 1, 0, 1, 1, 1, 1},
    {0, 1, 1, 1, 0, 1, 1},
    {0, 1, 1, 0, 1, 1, 1},
    {0, 0, 0, 1, 0, 1, 1}
};


const int right_digit_patterns[10][7] = {
   {1, 1, 1, 0, 0, 1, 0}
   {1, 1, 0, 0, 1, 1, 0}
   {1, 1, 0, 1, 1, 0, 0}
   {1, 0, 0, 0, 0, 1, 0}
   {1, 0, 1, 1, 1, 0, 0}
   {1, 0, 0, 1, 1, 1, 0}
   {1, 0, 1, 0, 0, 0, 0}
   {1, 0, 0, 0, 1, 0, 0}
   {1, 0, 0, 1, 0, 0, 0}
   {1, 1, 1, 0, 1, 0, 0}
};

int cabeca_pbm(FILE *file, int *width, int *height){
    char format[3];
    if(fscanf(file, %2s, format)!=1 || strcmp(format, "P1")!=0)){
        fprintf(stderr, "ERRO: não é um arquivo PBM válido\n");
        return -1; 
    }//leitura da formatação: checa se o formato P1 esta indicado


    if(fscanf(file, "%d %d", width, height)!=2)){
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
        if image[i]==NULL{
            fprintf("ERRO: falha de alocação da memória nas linhas da imagem\n");
            return NULL;
        }
    }

    //continuar a partir de height: parte que avisa falha na leitura da imagem
    for (i=0; i<height;i++){
        for(j=0;j<width;j++){
            if(fscanf(file,"%hhu", &image[i][j]!=1)){
                fprintf(stderr,"ERRO: falha em ler dados de imagem\n");
                return NULL;
            }
        }
    }


    return imagem;

}

//função que vai liberar a alocação de memória

void libera_pbm(unsigned char **image, int height){
    for (int i=0;i<height;i++){
        free(image[i]);
    }
    free(image);
}

//continuar com o código para liberação da memória (logo depois de free(image))
//aqui: https://pastebin.com/w2iiQvWk

