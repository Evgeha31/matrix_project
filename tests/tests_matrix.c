#include "matrix/matrix.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void test_create_matrix() {
    Matrix* matrix = create_matrix(2, 2);
    CU_ASSERT_PTR_NOT_NULL(matrix);
    CU_ASSERT_EQUAL(matrix->rows, 2);
    CU_ASSERT_EQUAL(matrix->cols, 2);
    free_matrix(matrix);
}

void test_add_matrices() {
    Matrix* A = create_matrix(2, 2);
    Matrix* B = create_matrix(2, 2);
    A->data[0][0] = 1; A->data[0][1] = 2;
    A->data[1][0] = 3; A->data[1][1] = 4;
    B->data[0][0] = 5; B->data[0][1] = 6;
    B->data[1][0] = 7; B->data[1][1] = 8;

    Matrix* result = add_matrices(A, B);
    CU_ASSERT_EQUAL(result->data[0][0], 6);
    CU_ASSERT_EQUAL(result->data[0][1], 8);
    CU_ASSERT_EQUAL(result->data[1][0], 10);
    CU_ASSERT_EQUAL(result->data[1][1], 12);

    free_matrix(A);
    free_matrix(B);
    free_matrix(result);
}

void test_multiply_matrices() {
    Matrix* A = create_matrix(2, 2);
    Matrix* B = create_matrix(2, 2);
    A->data[0][0] = 1; A->data[0][1] = 2;
    A->data[1][0] = 3; A->data[1][1] = 4;
    B->data[0][0] = 5; B->data[0][1] = 6;
    B->data[1][0] = 7; B->data[1][1] = 8;

    Matrix* result = multiply_matrices(A, B);
    CU_ASSERT_EQUAL(result->data[0][0], 19);
    CU_ASSERT_EQUAL(result->data[0][1], 22);
    CU_ASSERT_EQUAL(result->data[1][0], 43);
    CU_ASSERT_EQUAL(result->data[1][1], 50);

    free_matrix(A);
    free_matrix(B);
    free_matrix(result);
}

void test_transpose_matrix() {
    Matrix* matrix = create_matrix(2, 3);
    matrix->data[0][0] = 1; matrix->data[0][1] = 2; matrix->data[0][2] = 3;
    matrix->data[1][0] = 4; matrix->data[1][1] = 5; matrix->data[1][2] = 6;

    Matrix* result = transpose_matrix(matrix);
    CU_ASSERT_EQUAL(result->rows, 3);
    CU_ASSERT_EQUAL(result->cols, 2);
    CU_ASSERT_EQUAL(result->data[0][0], 1);
    CU_ASSERT_EQUAL(result->data[1][0], 2);
    CU_ASSERT_EQUAL(result->data[2][0], 3);

    free_matrix(matrix);
    free_matrix(result);
}

void test_determinant() {
    Matrix* matrix = create_matrix(3, 3);
    matrix->data[0][0] = 1; matrix->data[0][1] = 2; matrix->data[0][2] = 3;
    matrix->data[1][0] = 4; matrix->data[1][1] = 5; matrix->data[1][2] = 6;
    matrix->data[2][0] = 7; matrix->data[2][1] = 8; matrix->data[2][2] = 9;

    MatrixType det = determinant(matrix);
    CU_ASSERT_EQUAL(det, 0); // Детерминант этой матрицы равен 0

    free_matrix(matrix);
}

int main() {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Matrix Tests", NULL, NULL);
    CU_add_test(suite, "test_create_matrix", test_create_matrix);
    CU_add_test(suite, "test_add_matrices", test_add_matrices);
    CU_add_test(suite, "test_multiply_matrices", test_multiply_matrices);
    CU_add_test(suite, "test_transpose_matrix", test_transpose_matrix);
    CU_add_test(suite, "test_determinant", test_determinant);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
