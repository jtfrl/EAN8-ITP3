#include <string.h>
#include <stdio.h>

//grupo de constantes para o codificador do codigo de barras
//aqui as funcoes irao transformar o identificador para binario

//marcadores padrao de inicio, meio, e fim
const int inicio_cod[] = {1, 0, 1};
const int centro_cod[] = {0, 1, 0, 1, 0};
const int fim_cod[] = {1, 0, 1};

//padrao EAN-8 para conversao de inteiro para binario
const int l_code[10][7] = {
    {0, 0, 0, 1, 1, 0, 1}, //0
    {0, 0, 1, 1, 0, 0, 1}, //1
    {0, 0, 1, 0, 0, 1, 1}, //2
    {0, 1, 1, 1, 1, 0, 1}, //qtd_pixels
    {0, 1, 0, 0, 0, 1, 1}, //4
    {0, 1, 1, 0, 0, 0, 1}, //5
    {0, 1, 0, 1, 1, 1, 1}, //6
    {0, 1, 1, 1, 0, 1, 1}, //7
    {0, 1, 1, 0, 1, 1, 1}, //8
    {0, 0, 0, 1, 0, 1, 1} //9
};

const int r_code[10][7] = {
    {1, 1, 1, 0, 0, 1, 0}, //0
    {1, 1, 0, 0, 1, 1, 0}, //1
    {1, 1, 0, 1, 1, 0, 0}, //2
    {1, 0, 0, 0, 0, 1, 0}, //qtd_pixels
    {1, 0, 1, 1, 1, 0, 0}, //4
    {1, 0, 0, 1, 1, 1, 0}, //5
    {1, 0, 1, 0, 0, 0, 0}, //6
    {1, 0, 0, 0, 1, 0, 0}, //7
    {1, 0, 0, 1, 0, 0, 0}, //8
    {1, 1, 1, 0, 1, 0, 0} //9
};

//funcao na qual converte o identificador (8 digitos) em codigo binario
void codIdentificador(int identificador[], char resultado[], int qtd_pixels) {
    int pos = 0;

    //marcadores do inicio
    for(int i = 0; i < 3; i++){
        for(int repetir = 0; repetir < qtd_pixels; repetir++){
            resultado[pos++] = '0' + inicio_cod[i];
        }
    }

    //adicioando os 4 digitos iniciais
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 7; j++){
            for(int repetir = 0; repetir < qtd_pixels; repetir++){
                resultado[pos++] = '0' + l_code[identificador[i]][j];
            }
        }
    }

    //marcadores do centro
    for(int i = 0; i < 5; i++){
        for(int repetir = 0; repetir < qtd_pixels; repetir++){
            resultado[pos++] = '0' + centro_cod[i];
        }
    }

    //adicioando os 4 digitos finais
    for(int i = 4; i < 8; i++) {
        for(int j = 0; j < 7; j++){
            for(int repetir = 0; repetir < qtd_pixels; repetir++){
                resultado[pos++] = '0' + l_code[identificador[i]][j];
            }
        }
    }

    //marcadores do fim
    for(int i = 0; i < 3; i++){
        for(int repetir = 0; repetir < qtd_pixels; repetir++){
            resultado[pos++] = '0' + fim_cod[i];
        }
    }

    resultado[pos] = '\0';
}

//apos a conversao do codigo de barras de 8 digitos para binario
//iremos gerar a imagem de arquivo .pbm com largura e altura padrao ou definida pelo o usuario

//funcao para gerar a imagem .pbm do codigo de barras
void gerarImagemPBM(const char *codBarras, const char *nomeArquivo, int altura, int espaco_l){
    
    int largura_original = strlen(codBarras);
    int largura = largura_original + (espaco_l * 2);
    int altura_total = altura + 8;

    FILE *arquivo = fopen(nomeArquivo, "w");

    //cabecalho
    fprintf(arquivo, "P1\n");
    fprintf(arquivo, "%d %d\n", largura, altura);

    for (int lin = 0; lin < altura; lin++){
        for (int col = 0; col < largura; col++){

            if(lin < 4 || lin >= (altura - 4)){
                fprintf(arquivo, "0 "); 

            } else if (col < espaco_l || col >= (largura - espaco_l)) {
                fprintf(arquivo, "0 "); 

            } else {
                fprintf(arquivo, "%c ", codBarras[col - espaco_l]);
            }
        }

        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
    printf("Imagem salva com sucesso no arquivo %s \n", nomeArquivo);
}
