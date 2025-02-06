#ifndef DECODE_H
#define DECODE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include "io_pbm.h"

const int start_end_pattern[] = {1, 0, 1};
const int f_end_pattern[] = {1, 0, 1};       // right guard
const int c_end_pattern[] = {0, 1, 0, 1, 0}; // left guard
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
    {0, 0, 0, 1, 0, 1, 1}};

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
    {1, 1, 1, 0, 1, 0, 0}};

// funcao para achar os numeros entre as barras
int padroesBarra(unsigned char **image_novo, int width, int height, const int *padrao, int padraoTam)
{
    if (image_novo == NULL || padrao == NULL)
    {
        fprintf(stderr, "Ponteiro nulo detectado\n");
        return -1;
    }
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x <= width - padraoTam; x++)
        {
            int corretoBarra = 1;
            for (int p = 0; p < padraoTam; p++)
            {
                if (image_novo[y][x + p] != padrao[p])
                {
                    corretoBarra = 0;
                    break;
                }
            }
            if (corretoBarra)
            {
                return x;
            }
        }
    }
    return -1; // caso o padrão não seja achado
}

// função que vai pegar o código EAN-8 e converter para decimal
void extrai_bin(unsigned char **image_novo, int area, int bin_representa[])
{
    if (image_novo == NULL || bin_representa == NULL)
    {
        fprintf(stderr, "Ponteiro nulo detectado\n");
        return;
    }

    int row = 7;
    int start_column = 3 * area + 3; // 3 = espaçamento, 3 * area = pular tres areas;

    for (int x = 0; x < 28; x++)
    {
        bin_representa[x] = image_novo[row][start_column]; // Pega somente primeiro dígito da área
        start_column+= area;                // Avanço de área
    }

    start_column += area * 5; // Pula cinco áreas

    for (int x = 0; x < 28; x++)
    {
        bin_representa[x + 28] = image_novo[row][start_column]; // Pega somente primeiro dígito da área
        start_column += area;                     // Avanço de área
    }

    printf("Representacao binaria extraida: ");
    for (int i = 0; i < 56; i++)
    {
        printf("%d", bin_representa[i]);
    }
    printf("\n");
}

void decode_ean8(int bin_representa[], int decode_d[], int *status)
{
    // decodifica barras
    // busca pelos dígitos iniciais e os dígitos finais

    *status = 1; // inicia o valor de status como 1 (valor para estabilidade na decodificação)
    for (int i = 0; i < 4; i++)
    {
        // decodifica os numeros da esquerda
        int corretoEsq = 0; // 0 indica resultado para falso
        for (int j = 0; j < 10; j++)
        {
            int corretoEsq = 1;
            for (int k = 0; k < 7; k++)
            {
                if (bin_representa[i * 7 + k] != left_digit_patterns[j][k])
                {
                    corretoEsq = 0; // qualquer incoerência é detectada aqui
                    break;
                }
            }
            if (corretoEsq)
            {
                decode_d[i] = j;
                break;
            }
        }
        if (!corretoEsq)
        {
            *status = 0; // indica falha
            return;
        }
    }

    for (int i = 4; i < 8; i++)
    {
        // decodifica os numeros da direita
        int corretoDir = 0;
        for (int j = 0; j < 10; j++)
        {
            corretoDir = 1; // verificador de correção para direita
            for (int k = 0; k < 7; k++)
            {
                if (bin_representa[(i * 7) + k] != right_digit_patterns[j][k])
                {
                    corretoDir = 0;
                    break;
                }
            }
            if (corretoDir)
            {
                decode_d[i] = j;
                break;
            }
        }
        if (!corretoDir)
        {
            *status = 0;
            return;
        }
    }

    // essa opção deixa a declaração interna aos loops simples

    printf("Valores decodificados: ");
    for (int i = 0; i < 8; i++)
    {
        printf("%d ", decode_d[i]);
    }
    printf("\n");
}

int checasoma(int decode_d[])
{
    int soma = 0;
    for (int i = 0; i < 8; i++)
    {
        int pesosEAN = (i % 2 == 0 ? 3 : 1);
        soma += (decode_d[i]) * (pesosEAN); // considera o peso da soma
        // se par: 3; se ímpar: 1
    }
    // digito verificador
    int verifica = (int)(ceil(soma / 10)) * 10 - soma;
    return verifica;
}

#endif // previne redefinição com DECODE_H
