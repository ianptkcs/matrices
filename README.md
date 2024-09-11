# Matrix Product - Shortest Path

## Project Description

This project is a C program that solves the matrix multiplication problem in an optimized way. Through an analysis of matrix indices, the program finds the ideal order to perform the multiplication with the least possible number of scalar products. The recursive algorithm uses a divide-and-conquer strategy, keeping track of which matrix indices are eliminated at each stage of multiplication.

### Main Features

-   **Input file reading**: The program reads matrix dimensions from an input file.
-   **Shortest path calculation**: The algorithm finds the shortest path to multiply the matrices, minimizing the number of operations.
-   **Path visualization**: The program generates an output matrix that visualizes the path of index elimination during multiplication.
-   **Formatted output**: Generates an output file that displays the total number of scalar products and the best multiplication path.

## Files

### File Structure

-   `produto_matrizes.cpp`: Main file containing the project's source code.
-   `entrada2.txt`: Input file containing the matrix dimensions.
-   `saida2.txt`: Output file with the final result, including the number of scalar products and the path taken.

### Input

The file `entrada2.txt` should follow the following template:

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

### Output

The file `saida2.txt` will follow this template:

```
Total de multiplicacoes escalares = total

Chamadas à função: chamadas

Melhor ordem para realizar o produto:
    b x  c
    a x  b- c
 a- c x  d
```

## How to Run the Project

### Prerequisites

-   C compiler (such as `gcc`)
-   Visual Studio Code or any text editor compatible with C
-   Operating System: Windows, macOS, or Linux

### Compilation and Execution

1. Open the terminal/console in the project directory.
2. Compile the program with the command:

    ```bash
    gcc -o produto_matrizes produto_matrizes.c
    ```

3. After compilation, run the program with the command:

    ```bash
    ./produto_matrizes
    ```

4. The program will process the `entrada2.txt` file and generate the result in the `saida2.txt` file.

## Code Structure

The code has been divided into several functions for better organization and modularization:

-   **`produtos_escalares()`**: Calculates the number of scalar products in a multiplication of two matrices.
-   **`atualizar_indices_temporarios()`**: Updates temporary indices after eliminating an index during calculation.
-   **`achar_menor_caminho()`**: Main recursive function that finds the shortest multiplication path, minimizing the number of scalar products.
-   **`inicializar_duplas()`**: Reads input data and initializes the array of matrix dimensions.
-   **`imprimir_resultado()`**: Formats and writes the final result to the output file.
-   **`ler_entrada()`**: Reads the number of matrices from the input file.
-   **`criar_matriz_caminho()`**: Creates a visualization matrix for the multiplication path.
-   **`lidar_com_intervalos()`**: Handles multiplication intervals throughout the process.
-   **`liberar_memoria()`**: Frees the memory allocated during program execution.

## Considerations

### Complexity

The program uses a recursive algorithm to solve the matrix multiplication problem, resulting in an exponential time complexity in terms of _`O(n!)`_, where _`n`_ is the number of matrices. However, the _Divide and Conquer_ approach helps minimize the number of operations by finding the best path.

### Possible Improvements

-   **Use of Dynamic Programming**: Implement a dynamic programming approach to improve calculation efficiency.
-   **Memory Optimization**: Reduce the amount of dynamically allocated memory for temporary operations.

## Contribution

Feel free to make improvements or report errors. To do so:

1. Fork the project.
2. Create a branch for the new feature: `git checkout -b feature/new-feature`.
3. Commit your changes: `git commit -m 'Add new feature'`.
4. Push to the main branch: `git push origin feature/new-feature`.
5. Open a Pull Request.

## Author

-   **Ian Patrick da Costa Soares**

## License

This project is licensed under the terms of the [MIT License](LICENSE).
