#ifndef MATRIX_H
#define MATRIX_H

#include "../../include/config.h"

typedef struct {
    MatrixType** data; // Указатель на данные матрицы
    int rows;          // Количество строк
    int cols;          // Количество столбцов
} Matrix;

// Создание и освобождение памяти
Matrix* create_matrix(int rows, int cols);
void free_matrix(Matrix* matrix);

// Ввод и вывод
Matrix* load_matrix_from_file(const char* filename);


// Операции с матрицами
Matrix* copy_matrix(const Matrix* src);
Matrix* add_matrices(const Matrix* a, const Matrix* b);
Matrix* subtract_matrices(const Matrix* a, const Matrix* b);
Matrix* multiply_matrices(const Matrix* a, const Matrix* b);
Matrix* transpose_matrix(const Matrix* matrix);
MatrixType determinant(const Matrix* matrix);

#endif // MATRIX_H



