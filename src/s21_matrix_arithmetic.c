#include "s21_matrix.h"

int s21_sum_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
  int false = 0;
  if (its_ok_matrix(A) && its_ok_matrix(B)) {
    if (A->rows == B->rows && A->columns == B->columns) {
      false = s21_create_matrix(A->rows, A->columns, result);
      if (false == 0) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++)
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    } else {
      false = 2;
    }
  } else {
    false = 1;
  }
  return false;
}

int s21_sub_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
  int false = 0;
  if (its_ok_matrix(A) && its_ok_matrix(B)) {
    if (A->rows == B->rows && A->columns == B->columns) {
      false = s21_create_matrix(A->rows, A->columns, result);
      if (false == 0) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++)
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    } else {
      false = 2;
    }
  } else {
    false = 1;
  }
  return false;
}

int s21_mult_number(matrix_t* A, double number, matrix_t* result) {
  int false = 0;
  if (its_ok_matrix(A)) {
    false = s21_create_matrix(A->rows, A->columns, result);
    if (false == 0) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
          if (result->matrix[i][j] == -0) result->matrix[i][j] = 0;
        }
      }
    }
  } else {
    false = 1;
  }
  return false;
}

int s21_mult_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
  int false = 0;
  if (its_ok_matrix(A) && its_ok_matrix(B)) {
    if (A->rows == B->columns && A->columns == B->rows) {
      false = s21_create_matrix(A->rows, B->columns, result);
      if (false == 0) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < B->columns; j++) {
            for (int k = 0; k < B->rows; k++)
              result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    } else {
      false = 2;
    }
  } else {
    false = 1;
  }
  return false;
}

int s21_determinant(matrix_t* A, double* result) {
  int false = 0;
  *result = 0;
  if (its_ok_matrix(A)) {
    if (A->rows == A->columns) {
      if (A->rows != 1) {
        *result = s21_determinant_for_rows_more_one(A);
      } else {
        *result = A->matrix[0][0];
      }
    } else {
      false = 2;
    }
  } else {
    false = 1;
  }
  return false;
}

double s21_determinant_for_rows_more_one(matrix_t* A) {
  double res = 0;
  if (A->rows == 2) {
    res = A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
  } else {
    for (int i = 0; i < A->columns; i++) {
      matrix_t minor;
      s21_create_minor(A, &minor, 1, i + 1);
      res += pow((-1), i) * A->matrix[0][i] *
             s21_determinant_for_rows_more_one(&minor);
      s21_remove_matrix(&minor);
    }
  }
  return res;
}
