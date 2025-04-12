/**
 * @file output.h
 * @brief Функции для вывода матриц
 * 
 * Содержит функции для вывода матриц на экран и в файл
 */

#ifndef OUTPUT_H
#define OUTPUT_H

#include "../matrix/matrix.h"

/**
 * @brief Выводит матрицу в консоль 
 * @param matrix Указатель на матрицу для вывода
 * @note Для NULL-матрицы выводит предупреждение
 */
void print_matrix(const Matrix* matrix);

/**
 * @brief Сохраняет матрицу в текстовый файл
 * @param matrix Указатель на матрицу для сохранения
 * @param filename Имя файла для сохранения
 * @return 0 в случае успеха, -1 при ошибке
 */
void save_matrix_to_file(const Matrix* matrix, const char* filename);

#endif // OUTPUT_H
