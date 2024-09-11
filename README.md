# Produto de Matrizes - Menor Caminho

## Descrição do Projeto

Este projeto é um programa em C que resolve o problema de multiplicação de matrizes de forma otimizada. Através de uma análise dos índices das matrizes, o programa encontra a ordem ideal para realizar a multiplicação com o menor número possível de produtos escalares. O algoritmo recursivo utiliza a estratégia de divisão e conquista, mantendo o registro de quais índices das matrizes são eliminados em cada etapa da multiplicação.

### Funcionalidades Principais

-   **Leitura de arquivo de entrada**: O programa lê as dimensões das matrizes a partir de um arquivo de entrada.
-   **Cálculo do menor caminho**: O algoritmo encontra o menor caminho para multiplicar as matrizes, minimizando o número de operações.
-   **Visualização do caminho**: O programa gera uma matriz de saída que visualiza o caminho de eliminação dos índices durante a multiplicação.
-   **Saída formatada**: Gera um arquivo de saída que exibe o número total de produtos escalares e o melhor caminho de multiplicação.

## Arquivos

### Estrutura de Arquivos

-   `produto_matrizes.c`: Arquivo principal que contém o código-fonte do projeto.
-   `entrada2.txt`: Arquivo de entrada com as dimensões das matrizes.
-   `saida2.txt`: Arquivo de saída com o resultado final, incluindo o número de produtos escalares e o caminho percorrido.

### Entrada

O arquivo `entrada2.txt` deve seguir o seguinte formato:

```
Bla bla bla
bla bla bla
bla bla bla
bla bla bla
Quantidade de matrizes
N

Dimensoes das matrizes
a  b
b  c
c  d
d  e
```

### Saída

O arquivo `saida2.txt` conterá o seguinte formato:

```
Total de multiplicacoes escalares = total

Chamadas à função: chamadas

Melhor ordem para realizar o produto:
    b x  c
    a x  b- c
 a- c x  d
```

## Como Executar o Projeto

### Pré-requisitos

-   Compilador C (como `gcc`)
-   Visual Studio Code ou qualquer editor de texto compatível com C
-   Sistema Operacional: Windows, macOS ou Linux

### Compilação e Execução

1. Abra o terminal/console no diretório do projeto.
2. Compile o programa com o comando:

    ```bash
    gcc -o produto_matrizes produto_matrizes.c
    ```

3. Após a compilação, execute o programa com o comando:

    ```bash
    ./produto_matrizes
    ```

4. O programa irá processar o arquivo `entrada2.txt` e gerar o resultado no arquivo `saida2.txt`.

## Estrutura do Código

O código foi dividido em várias funções para melhor organização e modularização:

-   **`produtos_escalares()`**: Calcula o número de produtos escalares em uma multiplicação de duas matrizes.
-   **`atualizar_indices_temporarios()`**: Atualiza os índices temporários após eliminar um índice durante o cálculo.
-   **`achar_menor_caminho()`**: Função recursiva principal que encontra o menor caminho de multiplicação, minimizando o número de produtos escalares.
-   **`inicializar_duplas()`**: Lê os dados de entrada e inicializa o array de dimensões das matrizes.
-   **`imprimir_resultado()`**: Formata e escreve o resultado final no arquivo de saída.
-   **`ler_entrada()`**: Lê a quantidade de matrizes do arquivo de entrada.
-   **`criar_matriz_caminho()`**: Cria uma matriz de visualização para o caminho de multiplicação.
-   **`lidar_com_intervalos()`**: Trata os intervalos de multiplicação ao longo do processo.
-   **`liberar_memoria()`**: Libera a memória alocada durante a execução do programa.

## Considerações

### Complexidade

O programa utiliza um algoritmo recursivo para resolver o problema da multiplicação de matrizes, o que resulta em uma complexidade de tempo exponencial em termos de _`O(n!)`_, onde _`n`_ é o número de matrizes. No entanto, a abordagem _Dividir para Conquistar_ ajuda a minimizar o número de operações ao encontrar o melhor caminho.

### Melhorias Possíveis

-   **Uso de Programação Dinâmica**: Implementar uma abordagem de programação dinâmica para melhorar a eficiência do cálculo.
-   **Otimização de Memória**: Reduzir a quantidade de memória alocada dinamicamente para as operações temporárias.

## Contribuição

Sinta-se à vontade para fazer melhorias ou reportar erros. Para isso:

1. Faça um fork do projeto.
2. Crie um branch para a nova funcionalidade: `git checkout -b feature/nova-funcionalidade`.
3. Commit suas mudanças: `git commit -m 'Adiciona nova funcionalidade'`.
4. Envie para o branch principal: `git push origin feature/nova-funcionalidade`.
5. Abra um Pull Request.

## Autor

-   **Ian Patrick da Costa Soares**

## Licença

Este projeto está licenciado sob os termos da [MIT License](LICENSE).
