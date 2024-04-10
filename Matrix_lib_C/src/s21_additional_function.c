#include "s21_matrix.h"

void matrix_reduction(matrix_t *A, matrix_t *B, int r, int c) {
  int row = 0, column = 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (i != r && j != c) {
        B->matrix[row][column] = A->matrix[i][j];
        column++;
      }
    }
    column = 0;
    if (i != r) row++;
  }
}

int check_matrix(matrix_t *A) {
  return (A != NULL && A->rows > 0 && A->columns > 0);
}
