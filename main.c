#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define ROW_MAX 5
#define COLUMN_MAX 5


typedef enum {
    savePage = 0, transposePage, sumPage, multiplyPage
}Page;


typedef struct{
    int rows;
    int cols;
    int **data;
} Matrix;


Matrix *createMatrix(int row_size, int column_size);
void printMatrix(Matrix *matrix);
void getMatrix(Matrix *matrix);
void saveMatrix(Matrix *matrix);
void readMatrix(void);
void freeMatrix(Matrix *matrix);
Matrix *transposeMatrix(Matrix *matrix);
Matrix *sumMatrix(Matrix *matrix1,Matrix *matrix2);
Matrix *multiplyMatrix(Matrix *matrix1,Matrix *matrix2);
void clearScreen();
int mainPage(void);
int shouldContinue(int loopControl);


int main() {

    int loopControl = 1;
    while (loopControl) {

        int t_rows = 0 , t_cols= 0;
        Matrix *t_matrix, *t_matrix1, *t_matrix2;

        clearScreen();
        int operation = mainPage();
        switch (operation) {
            case savePage:
                clearScreen();
                printf("Saved Matrices:\n\n");
                printf("---------------------------------\n\n");

                readMatrix();

                printf("Press Enter to continue.");
                getchar();
                getchar();
                break;

            case transposePage:
                printf("How many rows wanted in matrix?: ");
                scanf("%d", &t_rows);
                printf("How many columns wanted in matrix?: ");
                scanf("%d", &t_cols);

                t_matrix = createMatrix(t_rows, t_cols);
                getMatrix(t_matrix);

                clearScreen();
                printMatrix(t_matrix);

                Matrix *transeposed_matrix = transposeMatrix(t_matrix);
                printMatrix(transeposed_matrix);
                saveMatrix(transeposed_matrix);
                loopControl = shouldContinue(loopControl);
                break;

            case sumPage:
                printf("How many rows wanted in matrix1?: ");
                scanf("%d", &t_rows);
                printf("How many columns wanted in matrix1?: ");
                scanf("%d", &t_cols);
                printf("\n");

                t_matrix1 = createMatrix(t_rows, t_cols);
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

                t_matrix2 = createMatrix(t_rows, t_cols);
                getMatrix(t_matrix2);

                Matrix *sum_matrix = sumMatrix(t_matrix1, t_matrix2);
                printMatrix(sum_matrix);
                saveMatrix(sum_matrix);
                loopControl = shouldContinue(loopControl);
                break;

            case multiplyPage:
                printf("How many rows wanted in matrix1?: ");
                scanf("%d", &t_rows);
                printf("How many columns wanted in matrix1?: ");
                scanf("%d", &t_cols);
                printf("\n");

                t_matrix1 = createMatrix(t_rows, t_cols);
                getMatrix(t_matrix1);

                printf("How many rows wanted in matrix2?: ");
                scanf("%d", &t_rows);
                printf("How many columns wanted in matrix2?: ");
                scanf("%d", &t_cols);
                printf("\n");

                t_matrix2 = createMatrix(t_rows, t_cols);
                getMatrix(t_matrix2);

                Matrix *m_matrix = multiplyMatrix(t_matrix1, t_matrix2);
                printMatrix(m_matrix);
                saveMatrix(m_matrix);
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


Matrix *createMatrix(int row_size, int column_size) {

    Matrix *matrix = (Matrix *) malloc(sizeof(Matrix));
    if (matrix == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

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


void saveMatrix(Matrix *matrix) {

    FILE *file = fopen("matrix.txt", "a");

    char answer;
    printf("Would you like to save this matrix? (Y/N): ");
    scanf(" %c", &answer);

    if (answer == 'Y' || answer == 'y') {
        char *t_name = (char *) calloc(1, 12);

        printf("What name you want to give to this matrix?: ");
        getchar();
        fgets(t_name, 12, stdin);
        printf("\n---------------------------------\n\n");

        fseek(file, 0, SEEK_END);
        fprintf(file, "%s\n", t_name);
        fprintf(file, "%d %d\n", matrix->rows, matrix->cols);

        for (int i = 0; i < matrix->rows; ++i) {
            for (int j = 0; j < matrix->cols; ++j) {
                fprintf(file, "%d\t", *(*(matrix->data + i) + j));
            }
            fprintf(file, "\n");
        }
    }
    fclose(file);
}


void readMatrix(void) {

    FILE *file = fopen("matrix.txt", "r");

    while (!feof(file)) {

        char *s_name = calloc(1, 12);
        int s_rows, s_cols, s_data;

        fscanf(file, "%s\n", s_name);
        fscanf(file, "%d %d\n", &s_rows, &s_cols);

        Matrix *s_matrix = createMatrix(s_rows,s_cols);

        printf("Matrix name = %s\n\n", s_name);
        for (int i = 0; i < s_rows; ++i) {
            for (int j = 0; j < s_cols; ++j) {
                fscanf(file, "%d\t", *(s_matrix->data + i) + j);
            }
            fscanf(file, "\n");
        }
        printMatrix(s_matrix);
        freeMatrix(s_matrix);
        printf("\n---------------------------------\n\n");
        fgetc(file);
    }
    fclose(file);
}


void freeMatrix(Matrix *matrix) {

    for (int i = 0; i < matrix->rows; ++i) {
        free(*(matrix->data + i));
    }

    free(matrix->data);
    free(matrix);
}


Matrix *sumMatrix(Matrix *matrix1, Matrix *matrix2) {

    Matrix *toplam = createMatrix(matrix1->rows,matrix1->cols);
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

    Matrix *carpim = createMatrix(matrix1->rows,matrix2->cols);
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

    Matrix *transpode_matrix = createMatrix(matrix->cols,matrix->rows);

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

    printf("0 - Saved Matrices\n\n");
    printf("1 - Transpose Matrix\n\n");
    printf("2 - Sum 2 Matrices\n\n");
    printf("3 - Multiply Matrices\n\n");

    printf("Type number for wanted operation: ");
    scanf("%d", &operation);

    if (operation < 0 || operation > 3)
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

