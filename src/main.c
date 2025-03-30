#include "matrix/matrix.h"
#include "output/output.h"
#include <stdio.h>
#include <assert.h>

int main() {
    // Создаем матрицы A, B, C и D
    Matrix* A = create_matrix(2, 2);
    Matrix* B = create_matrix(2, 2);
    Matrix* C = create_matrix(2, 2);
    Matrix* D = create_matrix(2, 2);

    // Заполняем матрицы A, B, C и D данными
    A->data[0][0] = 1; A->data[0][1] = 2;
    A->data[1][0] = 3; A->data[1][1] = 4;

    B->data[0][0] = 5; B->data[0][1] = 6;
    B->data[1][0] = 7; B->data[1][1] = 8;

    C->data[0][0] = 1; C->data[0][1] = 0;
    C->data[1][0] = 0; C->data[1][1] = 1;

    D->data[0][0] = 2; D->data[0][1] = 0;
    D->data[1][0] = 0; D->data[1][1] = 2;

    // Выводим матрицы
    printf("Matrix A:\n");
    print_matrix(A);

    printf("Matrix B:\n");
    print_matrix(B);

    printf("Matrix C:\n");
    print_matrix(C);

    printf("Matrix D:\n");
    print_matrix(D);

    Matrix* sum_AB = add_matrices(A, B);
    assert(sum_AB != NULL && "Error: A and B must have the same dimensions for addition.");

    printf("Matrix A + B:\n");
    print_matrix(sum_AB);

    // Вычисляем C^T (транспонированная C)
    Matrix* CT = transpose_matrix(C);
    assert(CT != NULL && "Error: Failed to transpose matrix C.");

    printf("Matrix C^T:\n");
    print_matrix(CT);

    // Вычисляем (A + B) × C^T
    Matrix* product = multiply_matrices(sum_AB, CT);
    assert(product != NULL && "Error: Incompatible dimensions for multiplication.");

    printf("Matrix (A + B) × C^T:\n");
    print_matrix(product);

    // Вычисляем (A + B) × C^T − D
    Matrix* result = subtract_matrices(product, D);
    assert(result != NULL && "Error: Incompatible dimensions for subtraction.");

    printf("Matrix (A + B) × C^T − D:\n");
    print_matrix(result);



    // Освобождаем память
    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
    free_matrix(D);
    free_matrix(sum_AB);
    free_matrix(CT);
    free_matrix(product);
    free_matrix(result);

    return 0;
}
