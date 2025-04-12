#include "../src/matrix/matrix.h"
#include "../src/output/output.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void test_main_operations(void) {
    Matrix* A = create_matrix(2, 2);
    Matrix* B = create_matrix(2, 2);
    Matrix* C = create_matrix(2, 2);
    Matrix* D = create_matrix(2, 2);

    A->data[0][0] = 1; A->data[0][1] = 2;
    A->data[1][0] = 3; A->data[1][1] = 4;

    B->data[0][0] = 5; B->data[0][1] = 6;
    B->data[1][0] = 7; B->data[1][1] = 8;

    C->data[0][0] = 1; C->data[0][1] = 0;
    C->data[1][0] = 0; C->data[1][1] = 1;

    D->data[0][0] = 2; D->data[0][1] = 0;
    D->data[1][0] = 0; D->data[1][1] = 2;

    Matrix* sum_AB = add_matrices(A, B);
    CU_ASSERT_PTR_NOT_NULL(sum_AB);
    CU_ASSERT_EQUAL(sum_AB->data[0][0], 6);
    CU_ASSERT_EQUAL(sum_AB->data[1][1], 12);
    
    Matrix* CT = transpose_matrix(C);
    CU_ASSERT_PTR_NOT_NULL(CT);
    CU_ASSERT_EQUAL(CT->data[0][0], 1);
    CU_ASSERT_EQUAL(CT->data[1][1], 1);
    
    Matrix* product = multiply_matrices(sum_AB, CT);
    CU_ASSERT_PTR_NOT_NULL(product);
    CU_ASSERT_EQUAL(product->data[0][0], 6);
    CU_ASSERT_EQUAL(product->data[1][1], 12);
    
    Matrix* result = subtract_matrices(product, D);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_EQUAL(result->data[0][0], 4);
    CU_ASSERT_EQUAL(result->data[1][1], 10);
    
    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
    free_matrix(D);
    free_matrix(sum_AB);
    free_matrix(CT);
    free_matrix(product);
    free_matrix(result);
}

void main_test_suite() {
    CU_pSuite suite = CU_add_suite("Main Tests", NULL, NULL);
    CU_add_test(suite, "test_main_operations", test_main_operations);
}
