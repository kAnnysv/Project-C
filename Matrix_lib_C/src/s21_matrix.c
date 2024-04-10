#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int err = 0;
  if (!(rows > 0 && columns > 0 && result != NULL)) {
    err = 1;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
    }
  }

  return err;
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }
  free(A->matrix);
  A->rows = 0;
  A->columns = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int err = 1;
  if (!(check_matrix(A) && check_matrix(B))) {
    err = 0;
  } else if (A->rows == B->rows && A->columns == B->columns) {
    for (int i = 0; i < A->rows; i++) {
      for (int k = 0; k < A->columns; k++) {
        if (fabs(A->matrix[i][k] - B->matrix[i][k]) > 1e-7) {
          err = 0;
          break;
        }
      }
    }
  } else {
    err = 0;
  }
  return err;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = 0;
  if (!(check_matrix(A) && check_matrix(B))) {
    err = 1;
  } else if (A->rows == B->rows && A->columns == B->columns) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][k] = A->matrix[i][k] + B->matrix[i][k];
      }
    }

  } else {
    err = 2;
  }
  return err;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = 0;
  if (!(check_matrix(A) && check_matrix(B))) {
    err = 1;
  } else if (A->rows == B->rows && A->columns == B->columns) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][k] = A->matrix[i][k] - B->matrix[i][k];
      }
    }

  } else {
    err = 2;
  }
  return err;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int err = 0;
  if (!check_matrix(A)) {
    err = 1;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][k] = A->matrix[i][k] * number;
      }
    }
  }
  return err;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = 0;
  if (A == NULL || B == NULL) {
    err = 1;
  } else if (A->columns == B->rows) {
    err = s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int k = 0; k < result->columns; k++) {
        result->matrix[i][k] = 0;
        for (int q = 0; q < A->columns; q++) {
          result->matrix[i][k] += A->matrix[i][q] * B->matrix[q][k];
        }
      }
    }

  } else {
    err = 2;
  }
  return err;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int err = 0;
  if (!(check_matrix(A) && result != NULL)) {
    err = 1;

  } else if (!s21_create_matrix(A->columns, A->rows, result)) {
    for (int i = 0; i < A->rows; i++) {
      for (int k = 0; k < A->columns; k++) {
        result->matrix[k][i] = A->matrix[i][k];
      }
    }
  } else {
    err = 1;
  }
  return err;
}

int s21_determinant(matrix_t *A, double *result) {
  int err = 0;
  *result = 0;
  if (!(check_matrix(A))) {
    err = 1;
  } else if (A->rows != A->columns) {
    err = 2;
  } else if (A->columns == 1) {
    *result = A->matrix[0][0];
  } else if (A->columns == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    double sign = 1, tmp_determinant = 0;
    for (int i = 0; i < A->columns; i++) {
      matrix_t temp_matrix;
      s21_create_matrix(A->rows - 1, A->columns - 1, &temp_matrix);
      matrix_reduction(A, &temp_matrix, 0, i);
      s21_determinant(&temp_matrix, &tmp_determinant);
      *result += tmp_determinant * sign * A->matrix[0][i];
      sign *= -1;
      s21_remove_matrix(&temp_matrix);
    }
  }
  return err;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  double tmp_determinant;
  int err = 0;
  if (!(check_matrix(A))) {
    err = 1;
  } else if (A->rows != A->columns) {
    err = 2;

  } else if (A->rows == 1 && A->columns == 1) {
    s21_create_matrix(A->rows, A->columns, result);
    result->matrix[0][0] = 1;

  } else {
    s21_create_matrix(A->rows, A->columns, result);

    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        matrix_t temp_matrix;
        s21_create_matrix(A->rows - 1, A->columns - 1, &temp_matrix);
        matrix_reduction(A, &temp_matrix, i, j);
        s21_determinant(&temp_matrix, &tmp_determinant);
        result->matrix[i][j] = tmp_determinant * pow(-1, i + j);
        s21_remove_matrix(&temp_matrix);
      }
    }
  }

  return err;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int err = 0;
  if (!(check_matrix(A) && result != NULL)) {
    err = 1;
  } else if (A->rows == A->columns) {
    double tmp_determinant = 0;
    err = s21_determinant(A, &tmp_determinant);
    if ((int)tmp_determinant != 0 && !err) {
      s21_create_matrix(A->rows, A->columns, result);
      if (A->rows == 1) {
        result->matrix[0][0] = A->matrix[0][0];
      } else {
        matrix_t tmp_calc_compl = {0};
        err = s21_calc_complements(A, &tmp_calc_compl);

        if (!err) {
          matrix_t tmp_transpose = {0};
          err = s21_transpose(&tmp_calc_compl, &tmp_transpose);
          if (!err) {
            err = s21_mult_number(&tmp_transpose, 1 / tmp_determinant, result);
          }
          s21_remove_matrix(&tmp_transpose);
        }
        s21_remove_matrix(&tmp_calc_compl);
      }
    } else {
      err = 2;
    }
  } else {
    err = 2;
  }
  return err;
}

// void print_matrix(matrix_t *res) {
//   for (int i = 0; i < res->rows; i++) {
//     for (int j = 0; j < res->columns; j++) {
//       printf("%lf ", res->matrix[i][j]);
//     }
//     printf("\n");
//   }
// }

// int main() {
//   matrix_t mat;
//   s21_create_matrix(5, 5, &mat);
//   print_matrix(&mat);

//   return 0;
// }