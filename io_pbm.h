#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include "id_main.c" 
#include "ean8.h" 
#define WIDTH 209
#define HEIGHT 58   
#define START_STOP_MOD_TAM 3
#define SAFETY_OFFSET 2

typedef struct{
    int width, height;
    unsigned char* pImg;
    unsigned char* pMeio;
    unsigned char* barra_larg;
}imgInfo;

const unsigned char* passaMargem(const unsigned char* buf){
    while (*buf==1){
        buf+=1;
    }
    return buf;
}

unsigned short largBarra(const unsigned char* buf){
    unsigned short larg_Barra=0;
    while (*buf==0){
        buf+=1;
        larg_Barra+=1;
    }
    buf-=larg_Barra;
    return larg_Barra;
}

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

//IMPORTANTE: a parte acima acho que vai ser válida para decode.h

void carrega_pbm(const char *filename, int image[HEIGHT][WIDTH]){
    FILE *arquivo=fopen(filename, "r");
    //aqui começa a leitura de fato e o carregamento em si
    if(file==NULL){
        perror("Erro ao abrir arquivo");
        exit(EXIT_FAILURE);
    }
    //podemos partir do ponto em que a checagem de formato já foi feita
    char format[3];
    int width, height;
    fscanf(arquivo, "%2s, %d, %d", format, &width, &height);

    //leitura dos dados a serem processados
    for(int y=0; y<HEIHT; y++){
        for(int x=0; x<WIDTH; x++){
            char c;
            do{
                c=fgetc(arquivo);
            }while(c!='0' && c!='1' && c!=EOF);
            if(c==EOF){
                fprintf(stderr, "Erro inesperado de fim de arquivo\n");
                fclose(file);
                exit(EXIT_FAILURE);
            }

            image[y][x]=(c=='1') ? 1 : 0;

            //avalia cada dado em imagem, sendo um ou zero 
        }
    }

    fclose(file);

}

void verbarra_pbm(int imagem[HEIGHT][WIDTH], int *x, int *y, int *larg, int *alt){
        //dectecta região da barra
        //procurar no doc tamanhos das dimensoes aceitas 
        //algumas variaveis foram adaptadas, tenha atenção nisso
        //continuar com verbarra_pbm aqui https://pastebin.com/9U3qFYx7
}
