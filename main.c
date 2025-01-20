#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cd_barras.h"

//gerador de codigo EAN-8
//gerar uma imagem com um codigo de barras a partir de um dado identificador

//padrao EAN-8 possui 7 digitos e 1 digito verificador
int main(int argc, char *argv[]){

    int digitos[8] = {};
    int soma = 0;

    const char *nomeArquivo = "cd_barras.pbm";

    //parametros padroes
    int altura = 200;
    int espaco_l = 20;
    int qtd_pixels = 5;

    if(argc < 2){
        printf("Por favor, digite um identificador de 8 numeros como argumento.\n");
        return -1;
    }

    FILE *arquivo = fopen(nomeArquivo, "r");
    if(arquivo){
        int resposta;
        printf("O arquivo já existe. Podemos sobreescreve-lo? Digite 1 para Sim ou 2 para nao:\n");
        scanf("%d", &resposta);
        fclose(arquivo);

        if(resposta == 2){
            printf("Arquivo resultante ja existe!\n");
            return -1;
        }
    }

    //recebe o segundo parametro, ja que o primeiro eh o nome do arquivo passado na linha do cmd
    char *entrada = argv[1];

    //verifica se a entrada tem 8 numeros
    if(strlen(entrada) != 8){
        printf("Identificador não possui 8 digitos.\n");
        return -1;
    }

    //conversao de string para numero
    for (int i = 0; i < 8; i++){
        digitos[i] = entrada[i] - '0';
    }

    //verificando se os dados estao corretos (somente valido de 0 a 9)
    for (int i = 0; i < 8; i++){
        if (digitos[i] < 0 || digitos[i] > 9){
            printf("Identificador contém valores não numéricos\n");
            return -1;
        }
    }

    //Leitura do Codigo de barras (calcular soma dos 7 digitos)
    for (int i = 0; i < 7; i++) {
        if (i % 2 == 0) {
            soma += (digitos[i] * 3);
        } else {
            soma += (digitos[i] * 1);
        }
    }

    //Digito verificador
    if (((soma + digitos[7]) % 10) == 0){
        printf("Leitura realizada com sucesso!.\n");
    } else {
        printf("O numero identificador digitado eh invalido.\n");
        return -1;
    }

    //verificando se o usuário passou o espacamento lateral no argumento
    if (argc > 2){
        espaco_l = atoi(argv[2]);
    }

    //verificando se a quantidade de pixels foi passada no argumento
    if (argc > 3){
        qtd_pixels = atoi(argv[3]);
    }

    //verificando se o usuário passou a altura no argumento
    if(argc > 4){
        altura = atoi(argv[4]);
    }

    //alocacao dinamica para o cod_barras
    int tamanho = 68 * qtd_pixels;
    char *cod_barras = (char *)malloc(tamanho * sizeof(char));

    printf("\n");

    //transforma o identificador de 8 digitos para binario (1, 0)
    codIdentificador(digitos, cod_barras, qtd_pixels);

    //gerar imagem .pbm com o codigo binario
    gerarImagemPBM(cod_barras, nomeArquivo, altura, espaco_l);

    free(cod_barras);

}