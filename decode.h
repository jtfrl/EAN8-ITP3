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

//função que vai pegar o código EAN-8 e converter para decimal
void extrai_bin(unsigned char **image_novo, int width, int height, int bin_representa[]){
    int index=0;
    for (int y=0; y<height; y++){
        for (int x=0; x<width; x++){
            if(image_novo[y][x]=='1'){
                bin_representa[index++]=1;
            }
            else{
                bin_representa[index++]=0;
            }
            if(index>=56){
                //para na analise dos 56 bits.
                return;
            }
        }
    }
	
	 printf("Representação binária extraída: ");
    for (int i = 0; i < 56; i++) {
        printf("%d", bin_representa[i]);
    }
    printf("\n");
}


void decode_ean8(int bin_representa[], int decode_d[], int *status){
    //decodifica barras
    //busca pelos dígitos iniciais e os dígitos finais

    *status=1; //inicia o valor de status como 1 (valor para estabilidade na decodificação)
    for (int i=0;i<4;i++){
        //decodifica os numeros da esquerda
        int corretoEsq=0; //0 indica resultado para falso
        for(int j=0;j<10;j++){
            int corretoEsq=1;
            for (int k=0; k<7; k++){
                if(bin_representa[i*7+k]!=left_digit_patterns[j][k]){
                    corretoEsq=0; //qualquer incoerência é detectada aqui
                    break;
                }
            }
            if(corretoEsq){
                decode_d[i]=j;
                break;
            }
        }
        if(!corretoEsq){
        *status=0; //indica falha
        return;
        }
    }

     for (int i=4;i<8;i++){
        //decodifica os numeros da direita
        int corretoDir=0;
        for(int j=0;j<10;j++){
            corretoDir=1; //verificador de correção para direita
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
        if(!corretoDir){
            *status=0;
            return;
        }
    }

//essa opção deixa a declaração interna aos loops simples

 printf("Valores decodificados: ");
    for (int i = 0; i < 8; i++) {
        printf("%d ", decode_d[i]);
    }
    printf("\n");

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
