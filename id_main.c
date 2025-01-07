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
            if(fscanf(file,"%hhu", &image[i][j]!=1)){ //alterar comparação de ponteiro
                fprintf(stderr,"ERRO: falha em ler dados de imagem\n");
                return NULL;
            }
        }
    }


    return image;

}

//função que vai liberar a alocação de memória

void libera_pbm(unsigned char **image, int height){
    for (int i=0;i<height;i++){
        free(image[i]);
    }
    free(image);
}

int main(int argc, char*argv[]){ 

    int image[HEIGHT][WIDTH] = {0}; 
    int x, y, larg, alt;
    int bin_representa[56]=0, decode_d[8]={0};
    //IMPORTANTE inlcuir variáveis usadas em carregapbm
    
    //main que vai receber o que o usuário irá fornecer
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
    

    int width, height;
    /* TESTE: verificando se o trecho está causando redefinição
    if(cabeca_pbm(arquivo, &width, &height)!=0){
        fclose(arquivo);
        return 1;
    }
    */
    fclose(arquivo);


    carrega_pbm(argv[1], image);
    //argv[1] guarda o nome do arquivo em .pbm
    verbarra_pbm(image, &x, &y, &larg, &alt);
    decode_ean8(bin_representa, decode_d);
    checasoma(decode_d);


    //cadeia de condição para decode.h; esboço a seguir

    /*
      if (verifica_ean8(image)) {
        printf("EAN-8 code detected\n");
    } else {
        printf("EAN-8 code not detected\n");
    }
    
    
    */
    //decodificação e checagem de soma
    int decode_r=decode_ean8(bin_representa, decode_d);
    int checaSoma=checasoma(decode_d);



    if(decode_r!=0 && checaSoma!=0){
        printf("Código EAN-8\n");
        for (int k=0; k<8;k++){
            printf("%d ", decode_d[k]);
        }
        printf("\n");
    }

    
    libera_pbm(image,height);

    return 0;
}


