#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Создание матрицы
Matrix* create_matrix(int rows, int cols) {
    assert(rows > 0 && cols > 0); 

    Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
    assert(matrix != NULL); 

    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = (MatrixType**)malloc(rows * sizeof(MatrixType*));
    assert(matrix->data != NULL); 

    for (int iter = 0; iter < rows; iter++) {
        matrix->data[iter] = (MatrixType*)malloc(cols * sizeof(MatrixType));
        assert(matrix->data[iter] != NULL); 
    }
    
    return matrix;
}

// Освобождение памяти
void free_matrix(Matrix* matrix) {
    if (matrix) {
        for (int iter = 0; iter < matrix->rows; iter++) 
            free(matrix->data[iter]); 
        free(matrix->data); 
        free(matrix); 
    }
}

// Загрузка матрицы из файла
Matrix* load_matrix_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    assert(file != NULL); 

    int rows, cols;
    fscanf(file, "%d %d", &rows, &cols);

    Matrix* matrix = create_matrix(rows, cols);
    for (int i = 0; i < rows; i++) 
        for (int j = 0; j < cols; j++) 
            fscanf(file, "%lf", &matrix->data[i][j]);

    fclose(file);
    return matrix;
}

// Копирование матрицы
Matrix* copy_matrix(const Matrix* src) {
    assert(src != NULL); 

    Matrix* dest = create_matrix(src->rows, src->cols);
    for (int i = 0; i < src->rows; i++) 
        for (int j = 0; j < src->cols; j++) 
            dest->data[i][j] = src->data[i][j];
        
    return dest;
}

// Сложение матриц
Matrix* add_matrices(const Matrix* a, const Matrix* b) {
    assert(a != NULL && b != NULL); 
    assert(a->rows == b->rows && a->cols == b->cols); 

    Matrix* result = create_matrix(a->rows, a->cols);
    for (int i = 0; i < a->rows; i++) 
        for (int j = 0; j < a->cols; j++) 
            result->data[i][j] = a->data[i][j] + b->data[i][j];
        
    return result;
}
//Разность матриц
Matrix* subtract_matrices(const Matrix* a, const Matrix* b) {
    assert(a != NULL && b != NULL); 
    assert(a->rows == b->rows && a->cols == b->cols); 

    Matrix* result = create_matrix(a->rows, a->cols);
    for (int i = 0; i < a->rows; i++) 
        for (int j = 0; j < a->cols; j++) 
            result->data[i][j] = a->data[i][j] - b->data[i][j];
        
    return result;
}

// Умножение матриц
Matrix* multiply_matrices(const Matrix* a, const Matrix* b) {
    assert(a != NULL && b != NULL); 
    assert(a->cols == b->rows); 

    Matrix* result = create_matrix(a->rows, b->cols);
    for (int i = 0; i < a->rows; i++) 
        for (int j = 0; j < b->cols; j++) {
            result->data[i][j] = 0;
            for (int k = 0; k < a->cols; k++)
                result->data[i][j] += a->data[i][k] * b->data[k][j];
        }
    return result;
}

// Транспонирование матрицы
Matrix* transpose_matrix(const Matrix* matrix) {
    assert(matrix != NULL); 

    Matrix* result = create_matrix(matrix->cols, matrix->rows);
    for (int i = 0; i < matrix->rows; i++) 
        for (int j = 0; j < matrix->cols; j++) 
            result->data[j][i] = matrix->data[i][j];

    return result;
}

// Рекурсивное вычисление детерминанта
MatrixType determinant(const Matrix* matrix) {
    assert(matrix != NULL); 
    assert(matrix->rows == matrix->cols); 

    if (matrix->rows == 1) 
        return matrix->data[0][0];

    if (matrix->rows == 2) 
        return matrix->data[0][0] * matrix->data[1][1] - matrix->data[0][1] * matrix->data[1][0];

    MatrixType det = 0;
    for (int col = 0; col < matrix->cols; col++) {
        Matrix* submatrix = create_matrix(matrix->rows - 1, matrix->cols - 1);
        for (int i = 1; i < matrix->rows; i++) {
            int subcol = 0;
            for (int j = 0; j < matrix->cols; j++) 
                if (j != col) { 
                    submatrix->data[i - 1][subcol] = matrix->data[i][j];
                    subcol++;
                }
        }
        det += (col % 2 == 0 ? 1 : -1) * matrix->data[0][col] * determinant(submatrix);
        free_matrix(submatrix);
    }
    return det;
}
