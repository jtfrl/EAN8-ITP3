#include <stdio.h>
#include <stdbool.h>//código a ser feito ainda
#define WIDTH 100 //colocar esse números no arquivo h
#define HEIGHT 100

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

void decode_ean8(int bin_representa[], int decode_d[]){
    //decodifica barras
}

int checasoma(int decode_d[]){
    int soma=0;
    for(int i=0;i<8;i++){
        soma+=decode_d[i] * (i%2==0? 3 : 1); //considera o peso da soma
    }
    //digito verificador
    int verifica=(ceil(soma/10))*10-soma;
    
    //talvez seja útil
    //verifica = (10 - (sum % 10)) % 10;
    //
    return verifica;
}

//os dois acima ficam em um arquivo h
