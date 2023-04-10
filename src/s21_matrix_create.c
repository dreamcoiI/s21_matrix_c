#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t* result) {
  int false = 0;
  if (rows < 1 || columns < 1) {
    false = 1;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(rows, sizeof(double));
    if (result->matrix == NULL) {
      false = 1;
    } else {
      for (int i = 0; i < result->rows; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          false = 1;
          break;
        }
      }
    }
  }
  return false;
}

void s21_remove_matrix(matrix_t* A) {
  if (A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i]) free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
  }
  if (A->columns) {
    A->columns = 0;
  }
  if (A->rows) {
    A->rows = 0;
  }
}

int its_ok_matrix(matrix_t* a) {
  int flag = 0;
  if (a && a->matrix != NULL && a->rows >= 1 && a->columns >= 1) {
    flag = 1;
  }
  return flag;
}  

int s21_create_minor(matrix_t* A, matrix_t* minor, int row, int columns) {
  int false = 0;
  if (its_ok_matrix(A)) {
    false = s21_create_matrix(A->rows - 1, A->columns - 1, minor);
    if (!false) {
      int r_min = 0, c_min = 0;
      for (int i = 0; i < A->rows; i++) {
        r_min = i;
        if (i > row - 1) r_min--;
        for (int j = 0; j < A->columns; j++) {
          c_min = j;
          if (j > columns - 1) c_min--;
          if (i != row - 1 && j != columns - 1) {
            minor->matrix[r_min][c_min] = A->matrix[i][j];
          }
        }
      }
    } else {
      false = 1;
    }
  } else {
    false = 1;
  }
  return false;
}
