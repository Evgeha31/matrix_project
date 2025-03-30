#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

extern void test_create_matrix();
extern void test_add_matrices();
extern void test_multiply_matrices();
extern void test_transpose_matrix();
extern void test_determinant();

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
