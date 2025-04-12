/**
 * @file matrix.h
 * @brief Заголовочный файл для работы с матрицами
 * 
 * Содержит определение структуры матрицы и основные операции над ней.
 */

#ifndef MATRIX_H
#define MATRIX_H

#include "../../include/config.h"

/**
 * @brief Структура, представляющая матрицу
 * 
 * Хранит данные матрицы и её размерности
 */
typedef struct {
    MatrixType** data; ///< Указатель на двумерный массив с элементами матрицы
    int rows;          ///< Количество строк в матрице
    int cols;          ///< Количество столбцов в матрице
} Matrix;

/**
 * @name Функции создания и освобождения памяти
 * @{
 */

/**
 * @brief Создает новую матрицу
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @return Указатель на созданную матрицу или NULL при ошибке
 */
Matrix* create_matrix(int rows, int cols);

/**
 * @brief Освобождает память, занятую матрицей
 * @param matrix Указатель на матрицу для освобождения
 */
void free_matrix(Matrix* matrix);

/** @} */

/**
 * @name Функции ввода/вывода
 * @{
 */

/**
 * @brief Загружает матрицу из файла
 * @param filename Имя файла для загрузки
 * @return Указатель на загруженную матрицу или NULL при ошибке
 */
Matrix* load_matrix_from_file(const char* filename);

/** @} */

/**
 * @name Операции с матрицами
 * @{
 */

/**
 * @brief Создает копию матрицы
 * @param src Исходная матрица для копирования
 * @return Указатель на новую копию матрицы
 */
Matrix* copy_matrix(const Matrix* src);

/**
 * @brief Складывает две матрицы
 * @param a Первая матрица
 * @param b Вторая матрица
 * @return Указатель на новую матрицу-сумму или NULL при ошибке
 */
Matrix* add_matrices(const Matrix* a, const Matrix* b);

/**
 * @brief Вычитает одну матрицу из другой
 * @param a Матрица, из которой вычитают
 * @param b Матрица, которую вычитают
 * @return Указатель на новую матрицу-разность или NULL при ошибке
 */
Matrix* subtract_matrices(const Matrix* a, const Matrix* b);

/**
 * @brief Умножает две матрицы
 * @param a Первая матрица
 * @param b Вторая матрица
 * @return Указатель на новую матрицу-произведение или NULL при ошибке
 */
Matrix* multiply_matrices(const Matrix* a, const Matrix* b);

/**
 * @brief Транспонирует матрицу
 * @param matrix Исходная матрица
 * @return Указатель на новую транспонированную матрицу
 */
Matrix* transpose_matrix(const Matrix* matrix);

/**
 * @brief Вычисляет определитель матрицы
 * @param matrix Матрица для вычисления
 * @return Значение определителя
 */
MatrixType determinant(const Matrix* matrix);

/** @} */

#endif // MATRIX_H



