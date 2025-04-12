/**
 * @file output.c
 * @brief Реализация функций вывода матриц
 * 
 * Содержит реализацию функций для вывода матриц на экран и в файл.
 */

#include "output.h"
#include <stdio.h>

/**
 * @brief Выводит матрицу в стандартный вывод
 * @param matrix Указатель на матрицу для вывода
 * @note Если matrix == NULL, функция завершится без вывода
 */
void print_matrix(const Matrix* matrix) {
    if (!matrix) return;
    
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%.2f ", matrix->data[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief Сохраняет матрицу в текстовый файл
 * @param matrix Указатель на сохраняемую матрицу
 * @param filename Путь к файлу для сохранения
 * @return Не возвращает значения
 * @note Если файл не может быть открыт, выводит ошибку через perror()
 */
void save_matrix_to_file(const Matrix* matrix, const char* filename) {
    if (!matrix) return;
    
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fprintf(file, "%d %d\n", matrix->rows, matrix->cols);
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            fprintf(file, "%.2f ", matrix->data[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}
