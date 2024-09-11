/* Ian Patrick da Costa Soares                      */
/* Turma 28.1                                       */
/* Exercício 2: Produto de Matrizes                 */
/*                                                  */
/* Programa compilado com Visual Studio Code 1.92.2 */

/* Incluir as bibliotecas usadas */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
- Esse programa, apesar de se tratar de matrizes, foca muito mais em seus índices.
- A cada multiplicação de matrizes, eliminamos um índice.
- Precisamos manter o registro de quais índices estão sendo eliminados.
- O menor caminho equivale ao menor número de produtos escalares.
*/

int CHAMADAS_FUNCAO = 0;

/* Definição de structs */
typedef struct menor_caminho mc;
typedef struct indice_absoluto indice_absoluto;

/* Estrutura para armazenar a melhor ordem e o número de produtos escalares */
struct menor_caminho
{
    int indice_eliminado;
    int produtos_escalares;
    int *registro_caminho;
};

/* Estrutura para manter o controle dos índices da função */
struct indice_absoluto
{
    int indice;
    int valor;
};

/* Declaração de funções */
mc achar_menor_caminho(indice_absoluto indices_absolutos[], int n);
indice_absoluto *atualizar_indices_temporarios(indice_absoluto indices_absolutos[], int n, int indice);
int produtos_escalares(indice_absoluto indices_absolutos[], int indice);
void inicializar_duplas(indice_absoluto *duplas, int n, FILE *entrada);
void imprimir_resultado(FILE *saida, mc menor_caminho, int n);
void ler_entrada(FILE *entrada, int *n);
char **criar_matriz_caminho(int n, mc menor_caminho);
int *lidar_com_intervalos(mc menor_caminho, char **matriz_caminho, int n, int i);
void liberar_memoria(indice_absoluto *duplas, mc menor_caminho, FILE *entrada, FILE *saida, int n);

/*--------------------------------------------------*/

/* Função que calcula o número de produtos escalares para multiplicar duas matrizes */
int produtos_escalares(indice_absoluto indices_absolutos[], int indice)
{
    return indices_absolutos[indice].valor * indices_absolutos[indice + 1].valor * indices_absolutos[indice - 1].valor;
}

/*--------------------------------------------------*/

/* Função que atualiza os índices temporários eliminando um índice específico */
indice_absoluto *atualizar_indices_temporarios(indice_absoluto indices_absolutos[], int novo_tamanho, int indice)
{
    indice_absoluto *ia = (indice_absoluto *)malloc(novo_tamanho * sizeof(indice_absoluto));
    int x = 0;
    for (int i = 0; i < novo_tamanho; i++)
    {
        if (i == indice)
        {
            x = 1;
        }
        ia[i] = indices_absolutos[i + x];
    }
    return ia;
}

/*--------------------------------------------------*/

/* Função principal que encontra o menor caminho para multiplicação das matrizes */
mc achar_menor_caminho(indice_absoluto indices_absolutos[], int n)
{
    CHAMADAS_FUNCAO++;
    mc menor_caminho;

    // Caso base
    if (n == 3)
    {
        menor_caminho.indice_eliminado = indices_absolutos[1].indice;
        menor_caminho.produtos_escalares = produtos_escalares(indices_absolutos, 1);
        menor_caminho.registro_caminho = (int *)malloc(sizeof(int));
        menor_caminho.registro_caminho[0] = menor_caminho.indice_eliminado;
        return menor_caminho;
    }

    // Caso recursivo
    menor_caminho.indice_eliminado = indices_absolutos[1].indice;
    mc caminho_auxiliar = achar_menor_caminho(atualizar_indices_temporarios(indices_absolutos, n - 1, 1), n - 1);
    menor_caminho.produtos_escalares = produtos_escalares(indices_absolutos, 1) + caminho_auxiliar.produtos_escalares;
    menor_caminho.registro_caminho = (int *)malloc((n - 2) * sizeof(int));
    menor_caminho.registro_caminho[0] = menor_caminho.indice_eliminado;

    /* Atualiza o registro de caminho */
    for (int i = 1; i < n - 2; i++)
    {
        menor_caminho.registro_caminho[i] = caminho_auxiliar.registro_caminho[i - 1];
    }

    /* Verifica se há um caminho menor e, se houver, atualiza o caminho */
    for (int i = 2; i < n - 1; i++)
    {
        mc caminho_temporario;
        caminho_temporario.indice_eliminado = indices_absolutos[i].indice;
        caminho_auxiliar = achar_menor_caminho(atualizar_indices_temporarios(indices_absolutos, n - 1, caminho_temporario.indice_eliminado), n - 1);
        caminho_temporario.produtos_escalares = produtos_escalares(indices_absolutos, i) + caminho_auxiliar.produtos_escalares;
        if (caminho_temporario.produtos_escalares < menor_caminho.produtos_escalares)
        {
            menor_caminho.produtos_escalares = caminho_temporario.produtos_escalares;
            menor_caminho.indice_eliminado = caminho_temporario.indice_eliminado;
            menor_caminho.registro_caminho[0] = menor_caminho.indice_eliminado;
            for (int i = 1; i < n - 2; i++)
            {
                menor_caminho.registro_caminho[i] = caminho_auxiliar.registro_caminho[i - 1];
            }
        }
    }
    return menor_caminho;
}

/*--------------------------------------------------*/

/* Função para inicializar o array de matrizes e suas dimensões */
void inicializar_duplas(indice_absoluto *duplas, int n, FILE *entrada)
{
    char linha[71];
    fseek(entrada, 0, SEEK_SET);

    while (!feof(entrada))
    {
        fgets(linha, sizeof(linha), entrada);
        if (strcmp(linha, "Dimensoes das matrizes\n") == 0)
        {
            for (int i = 0; i < n; i++)
            {
                duplas[i].indice = i;
                duplas[i + 1].indice = i + 1;
                fscanf(entrada, "%d %d", &duplas[i].valor, &duplas[i + 1].valor);
            }
        }
    }
}

/*--------------------------------------------------*/

/* Função para ler o valor de 'n' do arquivo de entrada */
void ler_entrada(FILE *entrada, int *n)
{
    char linha[71];
    while (!feof(entrada))
    {
        fgets(linha, sizeof(linha), entrada);
        if (strcmp(linha, "Quantidade de matrizes\n") == 0)
        {
            fscanf(entrada, "%d", n);
            break;
        }
    }
}

/*--------------------------------------------------*/

/* Função para criar a matriz de caminho */
char **criar_matriz_caminho(int n, mc menor_caminho)
{
    /* Aloca a matriz de caminho */
    char **matriz_caminho = (char **)malloc((n - 1) * sizeof(char *));
    for (int i = 0; i < n - 1; i++)
    {
        matriz_caminho[i] = (char *)malloc(n * sizeof(char));
        memset(matriz_caminho[i], 'o', n);
    }

    /* Preenche a matriz de caminho com 'o' */
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matriz_caminho[i][j] = 'o';
        }
    }

    /* Preenche os indices eliminados com 'x' e os intervalos formados com '-' */
    for (int i = 0; i < n - 1; i++)
    {
        matriz_caminho[i][menor_caminho.registro_caminho[i] - 1] = 'x';
        for (int j = i; j < n - 1; j++)
        {
            matriz_caminho[j][menor_caminho.registro_caminho[i] - 1] = '-';
        }
    }

    return matriz_caminho;
}

/*--------------------------------------------------*/

/* Função para lidar com os intervalos */
int *lidar_com_intervalos(mc menor_caminho, char **matriz_caminho, int n, int i)
{
    /* Aloca a linha */
    int *linha = (int *)malloc(4 * sizeof(int));
    memset(linha, 0, 4 * sizeof(int));

    /* Preenche a linha com as matrizes que estão sendo multiplicadas */
    linha[1] = menor_caminho.registro_caminho[i];
    linha[2] = menor_caminho.registro_caminho[i] + 1;

    /* Verifica se há um intervalo à esquerda */
    if (menor_caminho.registro_caminho[i] - 2 > 0 && matriz_caminho[i][menor_caminho.registro_caminho[i] - 2] == '-')
    {
        int k = 2;
        while (menor_caminho.registro_caminho[i] - k > 0 && matriz_caminho[i][menor_caminho.registro_caminho[i] - k - 1] == '-')
        {
            k++;
        }
        linha[0] = menor_caminho.registro_caminho[i] - k + 1;
    }

    /* Verifica se há um intervalo à direita */
    if (menor_caminho.registro_caminho[i] + 1 < n && matriz_caminho[i][menor_caminho.registro_caminho[i]] == '-')
    {
        int k = 2;
        while (menor_caminho.registro_caminho[i] + k < n && matriz_caminho[i][menor_caminho.registro_caminho[i] + k - 1] == '-')
        {
            k++;
        }
        linha[3] = menor_caminho.registro_caminho[i] + k;
    }

    return linha;
}

/*--------------------------------------------------*/

/* Função para imprimir o resultado no arquivo de saída */
void imprimir_resultado(FILE *saida, mc menor_caminho, int n)
{
    /* Cria uma matriz para visualizar o caminho */

    /* Imprime o resultado no arquivo */
    fprintf(saida, "Exemplo de arquivo de saida \n");
    fprintf(saida, "Exercicio 2\n");
    fprintf(saida, "Produto de Matrizes\n");
    fprintf(saida, "\nTotal de multiplicacoes escalares = %d\n", menor_caminho.produtos_escalares);
    fprintf(saida, "\nChamadas à função: %d\n", CHAMADAS_FUNCAO);
    fprintf(saida, "\nMelhor ordem para realizar o produto:");

    /* Cria a matriz de caminho */
    char **matriz_caminho = criar_matriz_caminho(n, menor_caminho);

    /* Imprime o caminho conforme o padrão estabelecido */
    for (int i = 0; i < n - 1; i++)
    {
        /* Cria a linha para lidar com os intervalos */
        int *linha = lidar_com_intervalos(menor_caminho, matriz_caminho, n, i);

        fprintf(saida, "\n");

        /* Imprime o intervalo */
        if (linha[0] == 0)
        {
            fprintf(saida, "   ");
        }
        else
        {
            fprintf(saida, "%2d-", linha[0]);
        }
        fprintf(saida, "%2d x %2d", linha[1], linha[2]);
        if (linha[3] != 0)
        {
            fprintf(saida, "-%2d", linha[3]);
        }
    }

    /* Libera a memória alocada */
    for (int i = 0; i < n - 1; i++)
    {
        free(matriz_caminho[i]);
    }
    free(matriz_caminho);
}

/*--------------------------------------------------*/

/* Função para liberar a memória alocada */
void liberar_memoria(indice_absoluto *duplas, mc menor_caminho, FILE *entrada, FILE *saida, int n)
{
    free(duplas);
    free(menor_caminho.registro_caminho);
    fclose(entrada);
    fclose(saida);
}

/*--------------------------------------------------*/

/* Função main modularizada */
int main()
{
    FILE *entrada = fopen("entrada2.txt", "r");
    FILE *saida = fopen("saida2.txt", "w");

    int n;
    ler_entrada(entrada, &n);

    /* Inicia um array de indices das matrizes */
    indice_absoluto *duplas = (indice_absoluto *)malloc((n + 1) * sizeof(indice_absoluto));

    /* Inicializa as dimensões das matrizes */
    inicializar_duplas(duplas, n, entrada);

    /* Acha o menor caminho */
    mc menor_caminho = achar_menor_caminho(duplas, n + 1);

    /* Imprime o resultado no arquivo de saída */
    imprimir_resultado(saida, menor_caminho, n);

    /* Libera a memória alocada */
    liberar_memoria(duplas, menor_caminho, entrada, saida, n);

    return 0;
}
