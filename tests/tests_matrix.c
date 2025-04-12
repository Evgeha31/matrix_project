#include "../src/matrix/matrix.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void test_create_matrix(void) {
    Matrix* m = create_matrix(2, 2);
    CU_ASSERT_PTR_NOT_NULL(m);
    CU_ASSERT_EQUAL(m->rows, 2);
    CU_ASSERT_EQUAL(m->cols, 2);
    free_matrix(m);
}

void test_free_matrix_null(void) {
    free_matrix(NULL);
}

void test_add_matrices(void) {
    Matrix* a = create_matrix(2, 2);
    Matrix* b = create_matrix(2, 2);
    
    a->data[0][0] = 1; a->data[0][1] = 2;
    a->data[1][0] = 3; a->data[1][1] = 4;
    
    b->data[0][0] = 5; b->data[0][1] = 6;
    b->data[1][0] = 7; b->data[1][1] = 8;
    
    Matrix* result = add_matrices(a, b);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_EQUAL(result->data[0][0], 6);
    CU_ASSERT_EQUAL(result->data[0][1], 8);
    CU_ASSERT_EQUAL(result->data[1][0], 10);
    CU_ASSERT_EQUAL(result->data[1][1], 12);
    
    free_matrix(a);
    free_matrix(b);
    free_matrix(result);
}

void test_subtract_matrices(void) {
    Matrix* a = create_matrix(2, 2);
    Matrix* b = create_matrix(2, 2);
    
    a->data[0][0] = 5; a->data[0][1] = 6;
    a->data[1][0] = 7; a->data[1][1] = 8;
    
    b->data[0][0] = 1; b->data[0][1] = 2;
    b->data[1][0] = 3; b->data[1][1] = 4;
    
    Matrix* result = subtract_matrices(a, b);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_EQUAL(result->data[0][0], 4);
    CU_ASSERT_EQUAL(result->data[0][1], 4);
    CU_ASSERT_EQUAL(result->data[1][0], 4);
    CU_ASSERT_EQUAL(result->data[1][1], 4);
    
    free_matrix(a);
    free_matrix(b);
    free_matrix(result);
}

void test_multiply_matrices(void) {
    Matrix* a = create_matrix(2, 3);
    Matrix* b = create_matrix(3, 2);
    
    a->data[0][0] = 1; a->data[0][1] = 2; a->data[0][2] = 3;
    a->data[1][0] = 4; a->data[1][1] = 5; a->data[1][2] = 6;
    
    b->data[0][0] = 7; b->data[0][1] = 8;
    b->data[1][0] = 9; b->data[1][1] = 10;
    b->data[2][0] = 11; b->data[2][1] = 12;
    
    Matrix* result = multiply_matrices(a, b);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_EQUAL(result->rows, 2);
    CU_ASSERT_EQUAL(result->cols, 2);
    CU_ASSERT_EQUAL(result->data[0][0], 58);
    CU_ASSERT_EQUAL(result->data[0][1], 64);
    CU_ASSERT_EQUAL(result->data[1][0], 139);
    CU_ASSERT_EQUAL(result->data[1][1], 154);
    
    free_matrix(a);
    free_matrix(b);
    free_matrix(result);
}

void test_transpose_matrix(void) {
    Matrix* m = create_matrix(2, 3);
    m->data[0][0] = 1; m->data[0][1] = 2; m->data[0][2] = 3;
    m->data[1][0] = 4; m->data[1][1] = 5; m->data[1][2] = 6;
    
    Matrix* result = transpose_matrix(m);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_EQUAL(result->rows, 3);
    CU_ASSERT_EQUAL(result->cols, 2);
    CU_ASSERT_EQUAL(result->data[0][0], 1);
    CU_ASSERT_EQUAL(result->data[0][1], 4);
    CU_ASSERT_EQUAL(result->data[1][0], 2);
    CU_ASSERT_EQUAL(result->data[1][1], 5);
    CU_ASSERT_EQUAL(result->data[2][0], 3);
    CU_ASSERT_EQUAL(result->data[2][1], 6);
    
    free_matrix(m);
    free_matrix(result);
}

void test_determinant(void) {
    Matrix* m1 = create_matrix(1, 1);
    m1->data[0][0] = 5;
    CU_ASSERT_EQUAL(determinant(m1), 5);
    free_matrix(m1);
    
    Matrix* m2 = create_matrix(2, 2);
    m2->data[0][0] = 1; m2->data[0][1] = 2;
    m2->data[1][0] = 3; m2->data[1][1] = 4;
    CU_ASSERT_EQUAL(determinant(m2), -2);
    free_matrix(m2);
    
    Matrix* m3 = create_matrix(3, 3);
    m3->data[0][0] = 1; m3->data[0][1] = 2; m3->data[0][2] = 3;
    m3->data[1][0] = 4; m3->data[1][1] = 5; m3->data[1][2] = 6;
    m3->data[2][0] = 7; m3->data[2][1] = 8; m3->data[2][2] = 9;
    CU_ASSERT_EQUAL(determinant(m3), 0);
    free_matrix(m3);
}

void test_copy_matrix(void) {
    Matrix* src = create_matrix(2, 2);
    src->data[0][0] = 1; src->data[0][1] = 2;
    src->data[1][0] = 3; src->data[1][1] = 4;
    
    Matrix* dest = copy_matrix(src);
    CU_ASSERT_PTR_NOT_NULL(dest);
    CU_ASSERT_EQUAL(dest->rows, 2);
    CU_ASSERT_EQUAL(dest->cols, 2);
    CU_ASSERT_EQUAL(dest->data[0][0], 1);
    CU_ASSERT_EQUAL(dest->data[0][1], 2);
    CU_ASSERT_EQUAL(dest->data[1][0], 3);
    CU_ASSERT_EQUAL(dest->data[1][1], 4);
    
    src->data[0][0] = 5;
    CU_ASSERT_EQUAL(dest->data[0][0], 1);
    
    free_matrix(src);
    free_matrix(dest);
}

void matrix_test_suite() {
    CU_pSuite suite = CU_add_suite("Matrix Tests", NULL, NULL);
    
    CU_add_test(suite, "test_create_matrix", test_create_matrix);
    CU_add_test(suite, "test_free_matrix_null", test_free_matrix_null);
    CU_add_test(suite, "test_add_matrices", test_add_matrices);
    CU_add_test(suite, "test_subtract_matrices", test_subtract_matrices);
    CU_add_test(suite, "test_multiply_matrices", test_multiply_matrices);
    CU_add_test(suite, "test_transpose_matrix", test_transpose_matrix);
    CU_add_test(suite, "test_determinant", test_determinant);
    CU_add_test(suite, "test_copy_matrix", test_copy_matrix);
}
