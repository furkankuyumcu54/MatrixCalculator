#include <stdio.h>
#include <stdlib.h>

#define ROW_MAX 5
#define COLUMN_MAX 5

typedef struct matrix {
    char name[10];
    int row_size;
    int column_size;
    int **matrix;
} Matrix;

int** createMatrix(int row_size, int column_size);
void printMatrix(int **matrix, int row_size, int column_size);
void transpose(int **matrix , int row_size , int column_size);
void clearScreen();

int main() {

    int rows, cols;
    printf("How many rows wanted in matrix?: ");
    scanf("%d", &rows);
    printf("How many columns wanted in matrix?: ");
    scanf("%d", &cols);

    int **matrix = createMatrix(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            *(*(matrix+i)+j) = (i+1) + (j+1);
        }
    }

    clearScreen();
    printMatrix(matrix, rows, cols);

    transpose(matrix,rows,cols);
    printMatrix(matrix, rows, cols);

    return 0;
}


void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #elif defined(__linux__)
        system("clear");
    #endif
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
            printf("%d\t", *(*(matrix + i) + j));
        }
        printf("\n");
    }
}


void transpose(int **matrix , int row_size , int column_size) {

    printf("Transposing ...\n");
    printf("---------------------------------\n");

    for (int i = 0; i < row_size; i++) {
        for (int j = i + 1; j < column_size; j++) {
            int temp = *(*(matrix + i) + j);
            *(*(matrix + i) + j) = *(*(matrix + j) + i);
            *(*(matrix + j) + i) = temp;
        }
    }
}
