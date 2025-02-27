#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <errno.h>
#include "pImg.h"

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

void carrega_pbm(const char *filename, int image_d[HEIGHT][WIDTH]){
	//image_d carrega os dados do PBM; diferente da variável image
	//em id_main.c
    FILE *arquivo=fopen(filename, "r");
    //aqui começa a leitura de fato e o carregamento em si
    if(arquivo==NULL){
        perror("Erro ao abrir arquivo");
        exit(EXIT_FAILURE);
    }
    //podemos partir do ponto em que a checagem de formato já foi feita
    char format[3];
    int width, height;
    fscanf(arquivo, "%2s %d %d", format, &width, &height);

    //leitura dos dados a serem processados
    for(int y=0; y<HEIGHT; y++){
        for(int x=0; x<WIDTH; x++){
            int c;
            do{
                c=fgetc(arquivo);
                //pula caracteres de espaço
                if(c==' ' || c=='\t' || c=='\n' || c=='\r' ){
                    continue;
                }
            }while(c!='0' && c!='1' && c!=EOF);
            if(c==EOF){
                fprintf(stderr, "Erro inesperado de fim de arquivo\n");
                fclose(arquivo);
                exit(EXIT_FAILURE);
            }

            image_d[y][x]=(c=='1') ? 1 : 0;

            //avalia cada dado em imagem, sendo um ou zero 
        }
    }

    fclose(arquivo);

}

void verbarra_pbm(unsigned char **image_novo, int *x, int *y, int *larg, int *alt){
        //converte a imagem de 2D para 1D
        unsigned char* pImg = (unsigned char*)malloc(HEIGHT * WIDTH *sizeof(unsigned char));
        for(int y=0;y<HEIGHT;y++){
            for(int x=0;x<WIDTH;x++){
                pImg[y*WIDTH+x]=(unsigned char)image_novo[y][x];
            }
        }

        //move para o meio

        int yMeio=HEIGHT/2;
        unsigned char* pMeio=pImg+yMeio*WIDTH;

        //Passa pela margem, para pegar a largura das barras
        const unsigned char* buf=passaMargem(pMeio);
        unsigned short larg_Barra=largBarra(buf);

        //Calcula as coodernadas e as dimensões da região da barra
        *x=(buf-pMeio)*larg_Barra;
        *y=yMeio;
        *larg=WIDTH; //assume que o código de barras abarca largura pre definida
        *alt=larg_Barra*(START_STOP_MOD_TAM*2+8*7+5);//total das áreas em codificação

        free(pImg);

}
 
