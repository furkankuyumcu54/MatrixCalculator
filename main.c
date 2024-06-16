#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define ROW_MAX 5
#define COLUMN_MAX 5


typedef enum {
    transposePage = 1, sumPage, multiplyPage
}Page;


typedef struct{
    char name[12];
    int rows;
    int cols;
    int **data;
} Matrix;


Matrix *createMatrix(char name[], int row_size, int column_size);
void printMatrix(Matrix *matrix);
void getMatrix(Matrix *matrix);
void freeMatrix(Matrix *matrix);
Matrix *transposeMatrix(Matrix *matrix);
Matrix *sumMatrix(Matrix *matrix1,Matrix *matrix2);
Matrix *multiplyMatrix(Matrix *matrix1,Matrix *matrix2);
void clearScreen();
int mainPage(void);
Page interface(Page page);
int shouldContinue(int loopControl);


int main() {

    char *t_name = (char *) calloc(1, 12);

    int loopControl = 1;
    while (loopControl) {

        int t_rows = 0 , t_cols= 0;
        Matrix *t_matrix, *t_matrix1, *t_matrix2;

        clearScreen();
        int operation = mainPage();
        switch (operation) {
            case transposePage:
                printf("What name you want to give to this matrix?: ");
                getchar();
                fgets(t_name, 12, stdin);
                printf("How many rows wanted in matrix?: ");
                scanf("%d", &t_rows);
                printf("How many columns wanted in matrix?: ");
                scanf("%d", &t_cols);

                t_matrix = createMatrix(t_name, t_rows, t_cols);
                getMatrix(t_matrix);

                clearScreen();
                printMatrix(t_matrix);

                Matrix *transeposed_matrix = transposeMatrix(t_matrix);
                printMatrix(transeposed_matrix);
                loopControl = shouldContinue(loopControl);
                break;

            case sumPage:
                printf("How many rows wanted in matrix1?: ");
                scanf("%d", &t_rows);
                printf("How many columns wanted in matrix1?: ");
                scanf("%d", &t_cols);
                printf("\n");

                t_matrix1 = createMatrix("matrix1", t_rows, t_cols);
                getMatrix(t_matrix1);

                printf("How many rows wanted in matrix2?: ");
                scanf("%d", &t_rows);
                printf("How many columns wanted in matrix2?: ");
                scanf("%d", &t_cols);
                printf("\n");
                if (t_matrix1->rows != t_rows || t_matrix1->cols != t_cols) {
                    printf("Both matrix' row and column size must be same.\n");
                    printf("Will return to main page in 5 seconds.\n");
                    sleep(5);
                    break;
                }

                t_matrix2 = createMatrix("matrix2", t_rows, t_cols);
                getMatrix(t_matrix2);

                printMatrix(sumMatrix(t_matrix1, t_matrix2));
                loopControl = shouldContinue(loopControl);
                break;

            case multiplyPage:
                printf("How many rows wanted in matrix1?: ");
                scanf("%d", &t_rows);
                printf("How many columns wanted in matrix1?: ");
                scanf("%d", &t_cols);
                printf("\n");

                t_matrix1 = createMatrix("matrix1", t_rows, t_cols);
                getMatrix(t_matrix1);

                printf("How many rows wanted in matrix2?: ");
                scanf("%d", &t_rows);
                printf("How many columns wanted in matrix2?: ");
                scanf("%d", &t_cols);
                printf("\n");

                t_matrix2 = createMatrix("matrix2", t_rows, t_cols);
                getMatrix(t_matrix2);

                printMatrix(multiplyMatrix(t_matrix, t_matrix2));
                loopControl = shouldContinue(loopControl);
                break;

            default:
                break;
        }
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


void freeMatrix(Matrix *matrix) {

    for (int i = 0; i < matrix->rows; ++i) {
        free(*(matrix->data + i));
    }

    free(matrix->data);
    free(matrix);
}


Matrix *sumMatrix(Matrix *matrix1, Matrix *matrix2) {

    if (matrix1->rows != matrix2->rows || matrix1->cols != matrix2->cols) {
        printf("Matrisler ayni boyutta olmalidir\\n\"");
        return NULL;
    }

    Matrix *toplam = createMatrix("toplam",matrix1->rows,matrix1->cols);
    for (int i = 0; i < matrix1->rows; ++i) {
        for (int j = 0; j < matrix1->cols; ++j) {
            *(*(toplam->data + i) + j) = *(*(matrix1->data + i) + j) + *(*(matrix2->data + i) + j);
        }
    }

    return toplam;
}


Matrix *multiplyMatrix(Matrix *matrix1, Matrix *matrix2) {

    if (matrix1->cols != matrix2->rows) {
        printf("ilk matrisin sutun sayisi ile ikinci matrisin satir sayisi esit olmalıdır");
        return NULL;
    }

    Matrix *carpim = createMatrix("carpim",matrix1->rows,matrix2->cols);
    for (int i = 0; i < matrix1->rows; ++i) {
        for (int j = 0; j < matrix2->cols; ++j) {
            *(*(carpim->data + i) + j) = 0;
            for (int k = 0; k < matrix1->cols; ++k) {
                carpim->data[i][j] += matrix1->data[i][k] * matrix2->data[k][j];
            }
        }
    }

    return carpim;
}


Matrix *transposeMatrix(Matrix *matrix) {

    printf("Transposing ...\n");
    printf("---------------------------------\n");

    Matrix *transpode_matrix = createMatrix("tranpose_matrix",matrix->cols,matrix->rows);

    for (int i = 0; i < matrix->rows; ++i) {
        for (int j = 0; j < matrix->cols; ++j) {
            transpode_matrix->data[j][i] = matrix->data[i][j];
        }
    }
    return transpode_matrix;
}


int mainPage(void) {

    int operation;
    printf("---------------------------------\n\n");
    printf("------- MATRIX CALCULATOR -------\n\n");
    printf("---------------------------------\n\n");

    printf("1 - Transpose Matrix\n\n");
    printf("2 - Sum 2 Matrices\n\n");
    printf("3 - Multiply Matrices\n\n");

    printf("Type number for wanted operation: ");
    scanf("%d", &operation);

    if (operation < 1 || operation > 3)
        exit(1);

    return operation;
}


int shouldContinue(int loopControl) {

    char answer;
    printf("Would you like to continue using calculator? (Y/N): ");
    scanf(" %c", &answer);

    if (answer == 'Y' || answer == 'y') {
        loopControl = 1;
    } else {
        loopControl = 0;
    }

    return loopControl;
}

