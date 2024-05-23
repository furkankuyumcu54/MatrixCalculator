#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW_MAX 5
#define COLUMN_MAX 5

typedef enum page {
    mainPage = 0, transposePage
}Page;

typedef struct matrix {
    char name[12];
    int rows;
    int cols;
    int **data;
} Matrix;

Matrix *createMatrix(char name[], int row_size, int column_size);
void printMatrix(Matrix *matrix);
void getMatrix(Matrix *matrix);
void transpose(Matrix *matrix);
void clearScreen();
Page interface(Page page);

int main() {

    int t_rows, t_cols;

    int operation = interface(mainPage);
    switch (operation) {
        case transposePage:
            printf("How many rows wanted in matrix?: ");
            scanf("%d", &t_rows);
            printf("How many columns wanted in matrix?: ");
            scanf("%d", &t_cols);

            Matrix *matrix = createMatrix("Matrix1", t_rows, t_cols);
            getMatrix(matrix);

            clearScreen();
            printMatrix(matrix);

            transpose(matrix);
            printMatrix(matrix);

        default:
            return 0;
    }

    return 0;
}


void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #elif defined(__linux__)
        system("clear");
    #endif
}


Matrix *createMatrix(char name[], int row_size, int column_size) {

    Matrix *matrix = (Matrix *) malloc(sizeof(Matrix));
    if (matrix == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    strncpy(matrix->name, name, sizeof(matrix->name));
    matrix->rows = row_size;
    matrix->cols = column_size;


    matrix->data = (int**) malloc(row_size * sizeof(int*));
    if (matrix->data == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < row_size; i++) {
        *(matrix->data + i) = (int*)malloc(column_size * sizeof(int));
        if (matrix->data[i] == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }
    }
    
    return matrix;
}


void printMatrix(Matrix *matrix) {

    printf("Matrix Name: %s\n", matrix->name);

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%d\t", *(*(matrix->data + i) + j));
        }
        printf("\n");
    }
}


void getMatrix(Matrix *matrix) {

    for (int i = 0; i < matrix->rows; ++i) {
        for (int j = 0; j < matrix->cols; ++j) {
            printf("%d. satırın %d sutununu giriniz: ", i+1, j+1);
            scanf("%d", (*(matrix->data + i) + j));
        }
    }

}


void transpose(Matrix *matrix) {

    printf("Transposing ...\n");
    printf("---------------------------------\n");

    strncpy(matrix->name, "Transposed1", sizeof(matrix->name));

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = i + 1; j < matrix->cols; j++) {
            int temp = *(*(matrix->data + i) + j);
            *(*(matrix->data + i) + j) = *(*(matrix->data + j) + i);
            *(*(matrix->data + j) + i) = temp;
        }
    }
}

Page interface(Page page) {

    Page operation;
    switch (page) {
        case mainPage:
            printf("---------------------------------\n\n");
            printf("------- MATRIX CALCULATOR -------\n\n");
            printf("---------------------------------\n\n");

            printf("1 - Transpose Matrix\n\n");

            printf("Type number for wanted operation: ");
            scanf("%d", &operation);
    }

    return operation;
}
