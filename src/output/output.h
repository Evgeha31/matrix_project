// output.h
#ifndef OUTPUT_H
#define OUTPUT_H

#include "../matrix/matrix.h"

void print_matrix(const Matrix* matrix);
void save_matrix_to_file(const Matrix* matrix, const char* filename);

#endif // OUTPUT_H