/**
 * @file matrix.c
 * @brief Реализация операций с матрицами
 * 
 * Содержит реализацию всех функций, объявленных в matrix.h
 */

#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * @brief Создает новую матрицу указанного размера
 * 
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @return Указатель на созданную матрицу
 * @note Выделяет память под структуру матрицы и её данные
 * @warning Требует последующего освобождения через free_matrix()
 */
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

/**
 * @brief Освобождает память, занятую матрицей
 * 
 * @param matrix Указатель на матрицу для освобождения
 * @note Корректно обрабатывает NULL-указатель
 */
void free_matrix(Matrix* matrix) {
    if (matrix) {
        for (int iter = 0; iter < matrix->rows; iter++) 
            free(matrix->data[iter]); 
        free(matrix->data); 
        free(matrix); 
    }
}

/**
 * @brief Загружает матрицу из текстового файла
 * 
 * Формат файла:
 * - Первые два числа: rows cols
 * - Последующие rows×cols чисел: элементы матрицы
 * 
 * @param filename Путь к файлу
 * @return Указатель на загруженную матрицу
 * @see save_matrix_to_file()
 */
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

/**
 * @brief Создает глубокую копию матрицы
 * 
 * @param src Исходная матрица для копирования
 * @return Новая независимая копия матрицы
 */
Matrix* copy_matrix(const Matrix* src) {
    assert(src != NULL); 

    Matrix* dest = create_matrix(src->rows, src->cols);
    for (int i = 0; i < src->rows; i++) 
        for (int j = 0; j < src->cols; j++) 
            dest->data[i][j] = src->data[i][j];
        
    return dest;
}

/**
 * @brief Складывает две матрицы поэлементно
 * 
 * @param a Первая матрица
 * @param b Вторая матрица
 * @return Новая матрица - результат сложения
 * @assert Размеры матриц должны совпадать
 */
Matrix* add_matrices(const Matrix* a, const Matrix* b) {
    assert(a != NULL && b != NULL); 
    assert(a->rows == b->rows && a->cols == b->cols); 

    Matrix* result = create_matrix(a->rows, a->cols);
    for (int i = 0; i < a->rows; i++) 
        for (int j = 0; j < a->cols; j++) 
            result->data[i][j] = a->data[i][j] + b->data[i][j];
        
    return result;
}

/**
 * @brief Вычитает две матрицы поэлементно
 * 
 * @param a Матрица, из которой вычитают
 * @param b Матрица, которую вычитают
 * @return Новая матрица - результат вычитания
 * @assert Размеры матриц должны совпадать
 */
Matrix* subtract_matrices(const Matrix* a, const Matrix* b) {
    assert(a != NULL && b != NULL); 
    assert(a->rows == b->rows && a->cols == b->cols); 

    Matrix* result = create_matrix(a->rows, a->cols);
    for (int i = 0; i < a->rows; i++) 
        for (int j = 0; j < a->cols; j++) 
            result->data[i][j] = a->data[i][j] - b->data[i][j];
        
    return result;
}

/**
 * @brief Умножает две матрицы
 * 
 * @param a Первая матрица (m×n)
 * @param b Вторая матрица (n×k)
 * @return Новая матрица размера m×k
 * @assert Число столбцов a должно совпадать с числом строк b
 */
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

/**
 * @brief Транспонирует матрицу
 * 
 * @param matrix Исходная матрица
 * @return Новая матрица - результат транспонирования
 */
Matrix* transpose_matrix(const Matrix* matrix) {
    assert(matrix != NULL); 

    Matrix* result = create_matrix(matrix->cols, matrix->rows);
    for (int i = 0; i < matrix->rows; i++) 
        for (int j = 0; j < matrix->cols; j++) 
            result->data[j][i] = matrix->data[i][j];

    return result;
}

/**
 * @brief Вычисляет определитель матрицы
 * 
 * Использует рекурсивный алгоритм разложения по первой строке
 * 
 * @param matrix Квадратная матрица
 * @return Значение определителя
 * @assert Матрица должна быть квадратной
 */
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
	det += (col % 2 == 0 ? -1 : 1) * matrix->data[0][col] * determinant(submatrix);
        free_matrix(submatrix);
    }
    return det;
}
