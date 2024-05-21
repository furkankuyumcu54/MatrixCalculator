#include <stdio.h>
#include <stdlib.h>

int** createMatrix(int row_size, int column_size);
void printMatrix(int **matrix, int row_size, int column_size);

        int main() {

    int rows = 5;
    int cols = 5;
    int **matrix = createMatrix(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * j;
        }
    }
    printMatrix(matrix, rows, cols);

    return 0;
}

int** createMatrix(int row_size, int column_size) {
    int **matrix = (int**) malloc(row_size * sizeof(int*));
    if (matrix == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < row_size; i++) {
        matrix[i] = (int*)malloc(column_size * sizeof(int));
        if (matrix[i] == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }
    }
    
    return matrix;
}

void printMatrix(int **matrix, int row_size, int column_size) {
    for (int i = 0; i < row_size; i++) {
        for (int j = 0; j < column_size; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}
