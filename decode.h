#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <math.h>
#include "io_pbm.c" 

#ifndef EAN8_DECODE

#define WIDTH 209 
#define HEIGHT 58
#define START_STOP_MOD_LENGTH 3
#define SAFETY_OFFSET 2

const unsigned char* passaMargem(const unsigned char* buf);
unsigned short largBarra(const unsigned char* buf);
void verbarra_pbm(int imagem[HEIGHT][WIDTH], int *x, int *y, int *larg, int *alt);

#endif //fim de declaração para EAN8_DECODE (uso de io_pbm)

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
   {1, 1, 1, 0, 0, 1, 0},
   {1, 1, 0, 0, 1, 1, 0},
   {1, 1, 0, 1, 1, 0, 0},
   {1, 0, 0, 0, 0, 1, 0},
   {1, 0, 1, 1, 1, 0, 0},
   {1, 0, 0, 1, 1, 1, 0},
   {1, 0, 1, 0, 0, 0, 0},
   {1, 0, 0, 0, 1, 0, 0},
   {1, 0, 0, 1, 0, 0, 0},
   {1, 1, 1, 0, 1, 0, 0}
};


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
        int pesosEAN=(i%2==0? 3 : 1); 
        soma+=(decode_d[i])*(pesosEAN); //considera o peso da soma
        //se par: 3; se ímpar: 1
    }
    //digito verificador
    int verifica=(int)(ceil(soma/10))*10-soma;
    return verifica;
}


