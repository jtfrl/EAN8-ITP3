#ifndef PIMG_H
#define PIMG_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define WIDTH 209
#define HEIGHT 58   
#define START_STOP_MOD_TAM 3 //marcador de final e início
#define SAFETY_OFFSET 2

typedef struct{
    int width, height;
    unsigned char* pImg;
    unsigned char* pMeio;
    unsigned char* barra_larg;
}imgInfo;

const unsigned char* passaMargem(const unsigned char* buf);
unsigned short largBarra(const unsigned char* buf);
void carrega_pbm(const char *filename, int image[HEIGHT][WIDTH]);
void verbarra_pbm(unsigned char **image_novo, int *x, int *y, int *larg, int *alt);


#endif //previne redefinição para PIMG_H
