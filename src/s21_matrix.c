#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows <= 0 || columns <= 0) {
    return FAIL_MATRIX;
  }
  double(*res_ptr)[columns] = NULL;
  res_ptr = (double(*)[columns])calloc(rows * columns, sizeof(double));
  if (!res_ptr) {
    RETURN_AND_PRINT_MASSAGE("s21_create_matrix: Fail to alocate memory\n",
                             FAIL_MATRIX);
  }
  result->columns = columns;
  result->rows = rows;
  result->matrix = (double **)res_ptr;
  return OK;
}

void s21_remove_matrix(matrix_t *A) {
  if (!A) {
    RETURN_AND_PRINT_MASSAGE("s21_remove_matrix: ptr on matrix is empty\n", 0);
  }
  if (A->columns <= 0) {
    RETURN_AND_PRINT_MASSAGE("s21_remove_matrix: Fail: columns <= 0\n", 0);
  }
  double(*A_ptr)[A->columns] = (double(*)[A->columns])A->matrix;
  free(A_ptr);
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (!A || !B || A->columns <= 0 || A->rows <= 0 || B->columns <= 0 ||
      B->rows <= 0) {
    RETURN_AND_PRINT_MASSAGE(
        "s21_eq_matrix: pointers on matrix is empty or rows <= 0 or columns <= "
        "0\n",
        FAIL_MATRIX);
  }
  if (A->columns != B->columns || A->rows != B->rows) {
    return FAIL_COMPLITE_MATRIX;
  }
  int status = SUCCESS;
  double(*A_ptr)[A->columns] = (double(*)[A->columns])A->matrix;
  double(*B_ptr)[B->columns] = (double(*)[B->columns])B->matrix;
  for (int i = 0; i < (A->columns); i++) {
    for (int j = 0; j < (A->rows); j++) {
      if (fabs(A_ptr[i][j] - B_ptr[i][j]) > EPS) {
        status = FAILURE;
        break;
      }
    }
  }
  return status;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!A || !B) {
    RETURN_AND_PRINT_MASSAGE(
        "s21_sum_matrix: Fail: pointers on matrixs are empty\n", FAIL_MATRIX);
  }
  if (A->columns <= 0 || A->rows <= 0 || B->columns <= 0 || B->rows <= 0) {
    return FAIL_MATRIX;
  }
  if (A->columns != B->columns || A->rows != B->rows) {
    return FAIL_COMPLITE_MATRIX;
  }
  int status = OK;
  status = s21_create_matrix(A->columns, A->rows, result);
  if (!status) {
    double(*A_ptr)[A->columns] = (double(*)[A->columns])A->matrix;
    double(*B_ptr)[B->columns] = (double(*)[B->columns])B->matrix;
    double(*res_ptr)[result->columns] =
        (double(*)[result->columns])result->matrix;
    double tmp = 0;

    for (int i = 0; i < (A->columns); i++) {
      for (int j = 0; j < (A->rows); j++) {
        tmp = A_ptr[i][j] + B_ptr[i][j];
        // сделать проверку на разные бесконечености (переполнения)
        res_ptr[i][j] = tmp;
      }
    }
  } else {
    return FAIL_MATRIX;
  }
  return status;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!A || !B) {
    RETURN_AND_PRINT_MASSAGE(
        "s21_sum_matrix: Fail: pointers on matrixs are empty\n", FAIL_MATRIX);
  }
  if (A->columns <= 0 || A->rows <= 0 || B->columns <= 0 || B->rows <= 0) {
    return FAIL_MATRIX;
  }
  if (A->columns != B->columns || A->rows != B->rows) {
    return FAIL_COMPLITE_MATRIX;
  }
  int status = OK;
  status = s21_create_matrix(A->columns, A->rows, result);
  if (!status) {
    double(*A_ptr)[A->columns] = (double(*)[A->columns])A->matrix;
    double(*B_ptr)[B->columns] = (double(*)[B->columns])B->matrix;
    double(*res_ptr)[result->columns] =
        (double(*)[result->columns])result->matrix;
    double tmp = 0;

    for (int i = 0; i < (A->columns); i++) {
      for (int j = 0; j < (A->rows); j++) {
        tmp = A_ptr[i][j] - B_ptr[i][j];
        // сделать проверку на разные бесконечености (переполнения)
        res_ptr[i][j] = tmp;
      }
    }
  } else {
    return FAIL_MATRIX;
  }
  return status;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (!A) {
    RETURN_AND_PRINT_MASSAGE(
        "s21_sum_matrix: Fail: pointer on matrix is empty\n", FAIL_MATRIX);
  }
  if (A->columns <= 0 || A->rows <= 0) {
    return FAIL_MATRIX;
  }
  int status = OK;
  status = s21_create_matrix(A->columns, A->rows, result);
  if (!status) {
    double(*A_ptr)[A->columns] = (double(*)[A->columns])A->matrix;
    double(*res_ptr)[result->columns] =
        (double(*)[result->columns])result->matrix;
    double tmp = 0;

    for (int i = 0; i < (A->columns); i++) {
      for (int j = 0; j < (A->rows); j++) {
        tmp = A_ptr[i][j] * number;
        // сделать проверку на разные бесконечености (переполнения)
        res_ptr[i][j] = tmp;
      }
    }
  } else {
    return FAIL_MATRIX;
  }
  return status;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!A || !B) {
    RETURN_AND_PRINT_MASSAGE(
        "s21_sum_matrix: Fail: pointer on matrix is empty\n", FAIL_MATRIX);
  }
  if (A->columns <= 0 || A->rows <= 0 || B->columns <= 0 || B->rows <= 0) {
    return FAIL_MATRIX;
  }
  if (A->rows != B->columns) {
    return FAIL_COMPLITE_MATRIX;
  }
  int status = OK;
  status = s21_create_matrix(A->columns, B->rows, result);
  if (!status) {
    double(*A_ptr)[A->columns] = (double(*)[A->columns])A->matrix;
    double(*B_ptr)[B->columns] = (double(*)[B->columns])B->matrix;
    double(*res_ptr)[result->columns] =
        (double(*)[result->columns])result->matrix;
    double tmp = 0;
    // Подумать, через какой цикл реализовать умножение матриц
  } else {
    return FAIL_MATRIX;
  }
  return status;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (!A) {
    RETURN_AND_PRINT_MASSAGE(
        "s21_sum_matrix: Fail: pointer on matrix is empty\n", FAIL_MATRIX);
  }
  if (A->columns <= 0 || A->rows <= 0) {
    return FAIL_MATRIX;
  }
  int status = OK;
  status = s21_create_matrix(A->columns, A->rows, result);
  if (!status) {
    double(*A_ptr)[A->columns] = (double(*)[A->columns])A->matrix;
    double(*res_ptr)[result->columns] =
        (double(*)[result->columns])result->matrix;
    for (int i = 0; i < (A->columns); i++) {
      for (int j = 0; j < (A->rows); j++) {
        res_ptr[j][i] = A_ptr[i][j];
      }
    }
  } else {
    return FAIL_MATRIX;
  }
  return status;
}