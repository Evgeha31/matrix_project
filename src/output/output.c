// output.c
#include "output.h"
#include <stdio.h>

void print_matrix(const Matrix* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%.2f ", matrix->data[i][j]);
        }
        printf("\n");
    }
}

void save_matrix_to_file(const Matrix* matrix, const char* filename) {
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