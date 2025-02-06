# EAN8-ITP3 ![C](https://img.shields.io/badge/language-C-blue)

---
![ATUALIZAÇÃO](https://img.shields.io/badge/ATUALIZA%C3%87%C3%83O-white?style=plastic&logoColor=violet&color=FF0012)
#### Agora, cada programa, gerador e identificador, ficam em pastas separadas. Para acessar o gerador, basta ir na pasta `G-EAN8` (autor: @victorjonhson); para ir para o identificador: `ID-EAN8`
Ainda trabalhando para melhorar o código de identificador. 
---

Programas para verificar e identificar código em EAN-8 em .pbm; também há um programa que gera uma imagem em PBM com o respectivo código em EAN8

O projeto consiste, então na verdade, em dois **códigos**: um para identificação de códigos em EAN8 (a partir de arquivos em .pbm) e um para gerar códigos EAN8.

A seguir, uma descrição breve de cada arquivo para **identificador de códigos EAN-8**:
- decode.h: checa os números que fazem parte do código em EAN8 no arquivo inserido. Ou seja: verifica e extrai os dígitos codificados na estrutura do código de barras, validando a conformidade com o padrão EAN-8;
- pImg.h: código fonte que dá suporte ao id_main.c para realizar os processos intermediários de identificação do código EAN-8 (serve de ponte entre o programa principal e o _header_ io_pbm.h);
- io_pbm.h: carregamento de imagem e detecção de barra em arquivos .pbm;
- id_main.c: código que vai receber o que o usuário inserir (nesse caso a imagem em .pbm). Especificamente, ele recebe a imagem .pbm inserida pelo usuário, chama as funções necessárias para ler o arquivo, detectar as barras e decodificar o código EAN-8, e finalmente apresenta o resultado ao usuário. Também executa o seguinte:
    - fornece funções para abrir e ler o conteúdo de arquivos .pbm, transformando-os em uma estrutura de dados utilizável pelo programa.

## Instruções para abertura do programa de identificador de códigos:
É recomendável que se use o PowerShell. Ao abrir:

    1. Coloque o caminho do arquivo (`C:\Users\caminho\do\arquivo\do\programa`)
    2. Compile o programa via gcc (`gcc -o nomedoprograma programa.c`)
    3. Execute o programa junto ao arquivo, indicando o nome do .pbm entre aspas (`.\nomedoprograma "arquivo.pbm`)

Obs.: o gerador, por enquanto, apenas apresenta os números em binário do .pbm, de forma truncada. Houve um problema na função para localizar o código EAN-8. 

Segue uma descrição breve de cada arquivo para **gerador de códigos EAN-8**:

O gerador do código EAN-8 é um programa modularizado em dois arquivos: o cd_barras.h e o main.c. 

De modo geral, o programa recebe um código identificador de 8 dígitos, no qual será transformado em binário (caso todas as condições tenham sido respeitadas) para que possa ser gerado o arquivo da imagem .pbm referente ao código de barras.

Sobre os arquivos: 
- cd_barras.h: contém todas as variáveis constantes e globais, além das funções: codificar o identificador em binário e gerar imagem .pbm.

- main.c: arquivo cujo estão todas as chamadas para a execução das funções do cd_barras.h, recebendo como parâmetro obrigatório um identificador de 8 dígitos que passará por uma série de validações estabelecidas pelo projeto. Na execução, o usuário ainda pode especificar o espaçamento lateral, tamanho da área da barra e a altura da imagem .pbm (porém, são parâmetros opcionais)

## Instruções para abertura do programa de gerador de códigos:

```
1. Abra o prompt de comando 

2. Digite >>> gcc main.c -o ean8 

3. ./ean8 <8digitos(obrigatório)> <espaçamento_lateral> <area_da_barra> <altura>
```
