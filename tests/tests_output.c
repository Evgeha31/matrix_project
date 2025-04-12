#include "../src/output/output.h"
#include "../src/matrix/matrix.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <string.h>

void test_print_matrix(void) {
    Matrix* m = create_matrix(2, 2);
    m->data[0][0] = 1.0; m->data[0][1] = 2.0;
    m->data[1][0] = 3.0; m->data[1][1] = 4.0;
    
    // Перенаправляем вывод в файл
    FILE* original_stdout = stdout;
    stdout = fopen("test_output.txt", "w");
    if (!stdout) {
        CU_FAIL("Не удалось открыть файл для вывода");
        free_matrix(m);
        return;
    }
    
    print_matrix(m);
    fclose(stdout);
    stdout = original_stdout;
    
    // Проверяем вывод
    FILE* f = fopen("test_output.txt", "r");
    if (!f) {
        CU_FAIL("Не удалось открыть файл для проверки");
        free_matrix(m);
        return;
    }
    
    char line1[100], line2[100];
    fgets(line1, 100, f);
    fgets(line2, 100, f);
    
    CU_ASSERT_STRING_EQUAL(line1, "1.00 2.00 \n");
    CU_ASSERT_STRING_EQUAL(line2, "3.00 4.00 \n");
    
    fclose(f);
    free_matrix(m);
    remove("test_output.txt");
}

void test_print_null_matrix(void) {
    // Перенаправляем вывод
    FILE* original_stdout = stdout;
    stdout = fopen("null_output.txt", "w");
    if (!stdout) {
        CU_FAIL("Не удалось перенаправить stdout");
        return;
    }
    
    print_matrix(NULL);
    
    fclose(stdout);
    stdout = original_stdout;
    remove("null_output.txt");
    
    CU_PASS("print_matrix(NULL) не вызвал падения");
}

void test_save_matrix_to_file(void) {
    Matrix* m = create_matrix(2, 2);
    m->data[0][0] = 1.0; m->data[0][1] = 2.0;
    m->data[1][0] = 3.0; m->data[1][1] = 4.0;
    
    const char* filename = "test_matrix.txt";
    
    // Просто вызываем функцию, не проверяем возвращаемое значение
    save_matrix_to_file(m, filename);
    
    // Проверяем содержимое файла
    FILE* f = fopen(filename, "r");
    CU_ASSERT_PTR_NOT_NULL(f);
    if (!f) {
        free_matrix(m);
        return;
    }
    
    int rows, cols;
    fscanf(f, "%d %d", &rows, &cols);
    CU_ASSERT_EQUAL(rows, 2);
    CU_ASSERT_EQUAL(cols, 2);
    
    float val;
    fscanf(f, "%f", &val); CU_ASSERT_EQUAL(val, 1.0);
    fscanf(f, "%f", &val); CU_ASSERT_EQUAL(val, 2.0);
    fscanf(f, "%f", &val); CU_ASSERT_EQUAL(val, 3.0);
    fscanf(f, "%f", &val); CU_ASSERT_EQUAL(val, 4.0);
    
    fclose(f);
    free_matrix(m);
    remove(filename);
}

void test_save_null_matrix(void) {
    // Просто проверяем что не упадет
    save_matrix_to_file(NULL, "test_null.txt");
    remove("test_null.txt");
    CU_PASS("save_matrix_to_file(NULL) не вызвал падения");
}

void output_test_suite() {
    CU_pSuite suite = CU_add_suite("Тесты вывода", NULL, NULL);
    if (!suite) {
        fprintf(stderr, "Ошибка создания тестового набора\n");
        return;
    }
    
    CU_add_test(suite, "Печать матрицы", test_print_matrix);
    CU_add_test(suite, "Печать NULL матрицы", test_print_null_matrix);
    CU_add_test(suite, "Сохранение матрицы", test_save_matrix_to_file);
    CU_add_test(suite, "Сохранение NULL матрицы", test_save_null_matrix);
}
