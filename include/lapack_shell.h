#ifndef LAPACK_SHELL_H
#define LAPACK_SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <lapacke.h>
#include <cblas.h>

/* Auxiliary routine: printing a rowmajor matrix */
 void print_matrix_rowmajor( char* desc, lapack_int m, lapack_int n, lapack_complex_double* mat, lapack_int ldm );

  /* Auxiliary routine: printing a colmajor matrix */
 void print_matrix_colmajor( char* desc, lapack_int m, lapack_int n, lapack_complex_double* mat, lapack_int ldm );


int calc_square_colmajor(lapack_complex_double inputs[], int input_size, lapack_complex_double righthands_outputs[]);

 #endif