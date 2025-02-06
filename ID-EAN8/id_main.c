#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "pImg.h" //o programa toma as declarações implícitas de io_pbm.h
#include "decode.h"


#define WIDTH 209
#define HEIGHT 58


int cabeca_pbm(FILE *arquivo, int *width, int *height){
    char format[3];
    if(fscanf(arquivo, "%2s", format)!=1 || strcmp(format, "P1")!=0){
        fprintf(stderr, "ERRO: não é um arquivo PBM válido\n");
        return -1; 
    }//leitura da formatação: checa se o formato P1 esta indicado


    if(fscanf(arquivo, "%d %d", width, height)!=2){
        fprintf(stderr, "ERRO: falha na leitura das dimensões da imagem\n");
        return -1;
    }//leitura de dimensões
    
    return 0;
}


unsigned char** dados_pbm(FILE *arquivo, int width, int height){
    unsigned char **image_novo = (unsigned char **)malloc(height *sizeof(unsigned char *));
    //cria espaço na memória para altura da imagem fornecida 
    if(image_novo==NULL){
        fprintf(stderr, "ERRO: falha na alocação de memória\n");
        return NULL;
    }

    for (int i=0; i<height;i++){
        image_novo[i]=(unsigned char *)malloc(width * sizeof(unsigned char));
        if (image_novo[i]==NULL){
            fprintf(stderr, "ERRO: falha de alocação da memória nas linhas da imagem\n");
            return NULL;
        }
    }

    for (int i=0; i<height;i++){
        for(int j=0;j<width;j++){
            if((fscanf(arquivo,"%hhu", &image_novo[i][j])!=1)){ //alterar comparação de ponteiro
                fprintf(stderr,"ERRO: falha em ler dados de imagem\n");
                return NULL;
            }
        }
    }
	for (int i=0; i<5; i++){
		for (int k=0; k<width; k++){
		printf("%c", image_novo[i][k]);
		}
		printf("\n");
	}
	


    return image_novo;

}

void libera_pbm(unsigned char **dadosImg, int height){
    for(int i=0;i<height;i++){
        free(dadosImg[i]);
    }    
    free(dadosImg);
}//libera a alocação com o ponteiro


int main(int argc, char*argv[]){ 
    int status;
    int x, y, larg, alt;
    int width, height;
    unsigned char **image_novo; //variável para receber dados do pbm
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
    
    if(cabeca_pbm(arquivo, &width, &height)!=0){
        fclose(arquivo);
        return 1;
	}
	

    
    image_novo=dados_pbm(arquivo, width, height);
    if(image_novo==NULL){
        fclose(arquivo);
        return 1;
    }

    fclose(arquivo); 
    
    verbarra_pbm(image_novo, &x, &y, &larg, &alt);
	
	int area=(int)((width-6)/67);
    extrai_bin(image_novo, area, bin_representa);
    decode_ean8(bin_representa, decode_d, &status);
	
	printf("Representacao binaria extraida: ");
    for (int i = 0; i < 56; i++) {
        printf("%d", bin_representa[i]);
    }
    printf("\n");
    

    
    int checaSoma=checasoma(decode_d);
    printf("Status: %d, Valor para checagem da soma: %d\n", status, checaSoma);

    if(status!=0 && checaSoma!=0){
        printf("Código EAN-8\n");
        for (int k=0; k<8;k++){
            printf("%d ", decode_d[k]);
        }
        printf("\n");
    }else{
        printf("Falha em decodificar o codigo EAN-8.\n");
    }
    
    libera_pbm(image_novo,height);
    //libera para image_novo

    printf("Pressione 'Enter' para sair\n");
    getchar();

    return 0;
}
