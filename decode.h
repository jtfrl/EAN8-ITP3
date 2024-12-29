#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include "io_pbm.h" 

#ifndef EAN8_DECODE

#define WIDTH 209 
#define HEIGHT 58
#define START_STOP_MOD_LENGTH 3
#define SAFETY_OFFSET 2

typedef struct{
    int width, height;
    unsigned char* pImg;
    unsigned char* pMeio;
    unsigned char* barra_larg;
}imgInfo;

const unsigned char* passaMargem(const unsigned char* buf);
unsigned short largBarra(const unsigned char* buf);
void verbarra_pbm(int imagem[HEIGHT][WIDTH], int *x, int *y, int *larg, int *alt);

#endif //fim de declaração para EAN8_DECODE (uso de io_pbm)

void decode_ean8(int bin_representa[], int decode_d[]){
    //decodifica barras
    //busca pelos dígitos iniciais e os dígitos finais

 
    for (int i=0;i<7;i++){
        //decodifica os numeros da esquerda
        for(int j=0;j<10;j++){
            if(bin_representa[i]=left_digit_patterns[j][i]){
                decode_d[i]=j;
                break;
            }
        }
    }

     for (int i=7;i<14;i++){
        //decodifica os numeros da direita
        for(int j=0;j<10;j++){
            if(bin_representa[i]=right_digit_patterns[j][i-7]){
                decode_d[i]=j;
                break;
            }
        }
    }

}

int checasoma(int decode_d[]){
    int soma=0;
    for(int i=0;i<8;i++){
        soma+=decode_d[i] * (i%2==0? 3 : 1); //considera o peso da soma
        //se par: 3; se ímpar: 1
    }
    //digito verificador
    int verifica=(ceil(soma/10))*10-soma;
    return verifica;
}


