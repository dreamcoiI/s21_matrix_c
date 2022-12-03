#include "s21_matrix.h"

int s21_eq_matrix(matrix_t* A, matrix_t* B) {
  int false = 1;
  if (its_ok_matrix(A) && its_ok_matrix(B)) {
    if ((A->columns != B->columns) || (A->rows != B->rows)) {
      false = 0;
    } else {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-6) false = 0;
        }
      }
    }
  } else {
    false = 0;
  }
  return false;
}
/*0 - OK
1 - Ошибка, некорректная матрица
2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой
нельзя провести вычисления и т.д.)*/

int s21_transpose(matrix_t* A, matrix_t* result) {
  int false = 0;
  if (its_ok_matrix(A)) {
    false = s21_create_matrix(A->columns, A->rows, result);
    if (false == 0) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++)
          result->matrix[j][i] = A->matrix[i][j];
      }
    }
  } else {
    false = 1;
  }
  return false;
}

int s21_calc_complements(matrix_t* A, matrix_t* result) {
  int false = 0;
  if (its_ok_matrix(A)) {
    if (A->rows == A->columns) {
      false = s21_create_matrix(A->rows, A->columns, result);
      if (false == 0) {
        if (A->rows == 1) {
          result->matrix[0][0] = A->matrix[0][0];
        } else {
          for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
              double res = 0;
              matrix_t minor;
              false = s21_create_minor(A, &minor, i + 1, j + 1);
              if (false == 0) {
                false = s21_determinant(&minor, &res);
                if (false == 0) result->matrix[i][j] = pow(-1, (i + j)) * res;
              }
              s21_remove_matrix(&minor);
            }
          }
        }
      }
    } else {
      false = 2;
    }
  } else {
    false = 2;
  }
  return false;
}

int s21_inverse_matrix(matrix_t* A, matrix_t* result) {
  int false = 0;
  if (its_ok_matrix(A)) {
    if (A->rows == A->columns) {
      double deter = 0;
      false = s21_determinant(A, &deter);
      if (false == 0 && deter != 0) {
        false = s21_create_matrix(A->rows, A->columns, result);
        if (false == 0) {
          matrix_t calc;
          false = s21_calc_complements(A, &calc);
          if (false == 0) {
            matrix_t transponse_mtrx;
            false = s21_transpose(&calc, &transponse_mtrx);
            if (false == 0) {
              s21_mult_number(&transponse_mtrx, 1 / deter, result);
            }
          }
          s21_remove_matrix(&calc);
        }
      } else {
        false = 2;
      }
    } else {
      false = 2;
    }
  } else {
    false = 1;
  }
  return false;
}