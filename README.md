# EAN8-ITP3
Código para verificar e identificar código em EAN-8 em .pbm; também gera uma imagem em PBM com o respectivo código em EAN8

O projeto consiste, então na verdade, em dois **códigos**: um para identificação de códigos em EAN8 (a partir de arquivos em .pbm) e um para gerar códigos EAN8.

A seguir, uma descrição breve de cada arquivo para **identificador de códigos EAN-8**:
- decode.h: checa os números que fazem parte do código em EAN8 no arquivo inserido. Ou seja: verifica e extrai os dígitos codificados na estrutura do código de barras, validando a conformidade com o padrão EAN-8;
- io_pbm.h: carregamento de imagem e detecção de barra em arquivos .pbm;
- id_main.c: código que vai receber o que o usuário inserir (nesse caso a imagem em .pbm). Especificamente, ele recebe a imagem .pbm inserida pelo usuário, chama as funções necessárias para ler o arquivo, detectar as barras e decodificar o código EAN-8, e finalmente apresenta o resultado ao usuário. Também executa o seguinte:
    - fornece funções para abrir e ler o conteúdo de arquivos .pbm, transformando-os em uma estrutura de dados utilizável pelo programa. Esta leitura é um passo essencial antes que qualquer processamento ou decodificação possa ocorrer. 
