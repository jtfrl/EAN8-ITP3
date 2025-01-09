#ifndef DECODE_H
#define DECODE_H

#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <math.h>
#include "io_pbm.h" 

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


void decode_ean8(int bin_representa[], int decode_d[], int *status){
    //decodifica barras
    //busca pelos dígitos iniciais e os dígitos finais

 
    for (int i=0;i<4;i++){
        //decodifica os numeros da esquerda
        for(int j=0;j<10;j++){
            int corretoEsq=1;
            for (int k=0; k<7; k++){
                if(bin_representa[i*7+k]!=left_digit_patterns[j][k]){
                    corretoEsq=0;
                    break;
                }
            }
            if(corretoEsq){
                decode_d[i]=j;
                break;
            }
        }
    }
    int val_corretoEsq=corretoEsq;

     for (int i=4;i<8;i++){
        //decodifica os numeros da direita
        for(int j=0;j<10;j++){
            int corretoDir=1; //verificador de correção para direita
            for (int k=0; k<7; k++){
                if(bin_representa[(i*7)+k]!=right_digit_patterns[j][k]){
                    corretoDir=0;
                    break;
                }
            }
            if(corretoDir){
                decode_d[i]=j;
                break;
            }
        }
    }
    int val_corretoDir=corretoDir;


    if(val_corretoEsq==0 && val_corretoDir==0){
        *status=0;
    }else{
        *status=1;//indica sucesso
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


#endif //previne redefinição com DECODE_H