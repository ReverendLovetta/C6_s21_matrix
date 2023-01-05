#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 0           // OK
#define FAIL_MATRIX 1  // Fail, uncorrect matrix
#define FAIL_COMPLITE_MATRIX \
  2  // fail вычисления (несовпадающие размеры матриц; матрица, для которой
     // нельзя провести вычисления и т.д.)

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

/*------------------------*/
/* Operations for matrix: */
/*------------------------*/

/* create matrix */
int s21_create_matrix(int rows, int columns, matrix_t *result);

/* reset matrix */
void s21_remove_matrix(matrix_t *A);

/* compare matrix */
#define SUCCESS 1
#define FAILURE 0

#define EPS 1E-7

int s21_eq_matrix(matrix_t *A, matrix_t *B);

/* sum matrix */
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/* sub matrix */
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/* mult_number matrix */
int s21_mult_number(matrix_t *A, double number, matrix_t *result);

/* mult matrix */
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/* transpose matrix */
int s21_transpose(matrix_t *A, matrix_t *result);

/* calc_complements matrix */
int s21_calc_complements(matrix_t *A, matrix_t *result);

/* determinant matrix */
int s21_determinant(matrix_t *A, double *result);

/* inverse matrix */
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

/*--------------------------*/
/* subfunctions for matrix: */
/*--------------------------*/

/* copy_matrix */
int copy_matrix(matrix_t *dest, matrix_t *res);

/* create random values for matrix */
int create_random_values(matrix_t *A);

#endif  // SRC_S21_MATRIX_H_