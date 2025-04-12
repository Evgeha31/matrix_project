#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void matrix_test_suite();
void output_test_suite();
void main_test_suite();

int main() {

    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    matrix_test_suite();
    output_test_suite();
    main_test_suite();

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}
